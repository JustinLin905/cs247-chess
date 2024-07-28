#include "Game.h"

#include <iostream>
#include <memory>

#include "../Player/ComputerPlayer/ComputerLevel1.h"
// #include "../Player/ComputerPlayer/ComputerLevel2.h"
// #include "../Player/ComputerPlayer/ComputerLevel3.h"
// #include "../Player/ComputerPlayer/ComputerLevel4.h"
#include "../Player/HumanPlayer.h"
#include "../PlayerType/PlayerType.h"

Game::Game(PlayerType::Type white, PlayerType::Type black) : _chess_board(std::make_shared<ChessBoard>()), _text_observer{std::make_shared<TextObserver>(_chess_board, std::cout)}, _graphics_observer{std::make_shared<GraphicsObserver>(_chess_board)}, _white{createPlayerPtr(white)}, _black{createPlayerPtr(black)} {}

std::unique_ptr<Player> Game::createPlayerPtr(PlayerType::Type type) {
    switch (type) {
        case PlayerType::Type::HUMAN:
            return std::make_unique<HumanPlayer>(Color::WHITE);
        case PlayerType::Type::COMPUTER_LEVEL1:
            return std::make_unique<ComputerLevel1>(Color::WHITE, _chess_board);
        default:
            throw std::invalid_argument("Invalid player type");
    }
}

void Game::initDefaultGame() {
    _chess_board->defaultSetup(_white, _black, _chess_board);
}

void Game::performMove(Move move, Color player_color) {
    auto initial = move.initial_pos;
    auto final = move.final_pos;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    std::shared_ptr<Piece> moving_piece = init_square.getPiece();

    // check if move is castle
    char king_char = player_color == Color::WHITE ? 'K' : 'k';
    if (moving_piece->getPieceChar() == king_char && (move.type == MoveType::KING_SIDE_CASTLE || move.type == MoveType::QUEEN_SIDE_CASTLE) && !moving_piece->hasMoved()) {
        auto castle_type = move.type;
        Position rook_init = {initial.r, castle_type == MoveType::KING_SIDE_CASTLE ? 7 : 0};
        Position rook_final = {initial.r, castle_type == MoveType::KING_SIDE_CASTLE ? 5 : 3};
        Move rook_move = {rook_init, rook_final, MoveType::DEFAULT};
        performMove(rook_move, player_color);

        // Square& rook_init_square = _chess_board->getSquare(rook_init);
        // Square& rook_final_square = _chess_board->getSquare(rook_final);
        // auto rook = rook_init_square.getPiece();
        // rook_init_square.disconnectPiece();
        // rook_final_square.setPiece(rook, false);
        // rook_final_square.getPiece()->setSquare(_chess_board->getSquarePtr(rook_final));
        // rook->setSquare(_chess_board->getSquarePtr(rook_final));
    }
    // if a piece was captured
    else if (final_square.getPiece() != nullptr) {
        Player& captured_player = player_color == Color::WHITE ? *_black : *_white;
        _chess_board->removeDeadPiece(final_square.getPiece());
    }

    // Move the piece
    init_square.disconnectPiece();
    final_square.setPiece(moving_piece, false);
    moving_piece->setSquare(_chess_board->getSquarePtr(final));

    // mark the piece as moved
    moving_piece->Moved();

    // update attack map
    _chess_board->updateAttackMap();
}

bool Game::makeTurn(Move move, Color player_color) {
    auto initial = move.initial_pos;
    auto final = move.final_pos;
    std::cout << initial << std::endl;
    std::cout << final << std::endl;

    // Check current player is in check
    bool in_check = false;
    if (player_color == Color::WHITE) {
        in_check = _white->inCheck();
        if (in_check) std::cout << "White is in check" << std::endl;
    } else if (_black->inCheck()) {
        in_check = _black->inCheck();
        if (in_check) std::cout << "Black is in check" << std::endl;
    }

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();
    if (piece_at_init == nullptr) return false;
    if (piece_at_init->getColor() != player_color) return false;

    std::unordered_set<Move> valid_moves = piece_at_init->getValidMoves();
    std::unordered_set<Move> valid_moves_out;

    // for (auto m : valid_moves) std::cout << m.initial_pos << " 2-> " << m.final_pos << std::endl;

    // simulate all moves to see if any move gets player out of check
    // This removes all moves that do not get player out of check/put the player into check
    for (auto it = valid_moves.begin(); it != valid_moves.end(); it++) simulateLegality(*it, player_color, valid_moves_out);

    // for (auto m : valid_moves_out) std::cout << m.initial_pos << " -> " << m.final_pos << std::endl;

    if (valid_moves_out.empty()) {
        std::cout << "No legal moves for this piece!" << std::endl;
        return false;
    }

    // for comparing moves regardless of move type. We now determine the type of move the player wants to make
    auto compare_moves = [initial, final](Move m) { return m.initial_pos == initial && m.final_pos == final; };
    auto it = std::find_if(valid_moves_out.begin(), valid_moves_out.end(), compare_moves);

    // print move
    // std::cout << "Move: " << move.initial_pos << " -> " << move.final_pos << std::endl;

    // If move is not in the piece's valid moves, return false
    if (it == valid_moves_out.end()) {
        std::cout << "Not found in legal moves. Legal moves for this piece: " << std::endl;
        for (auto m : valid_moves_out) std::cout << m.initial_pos << " -> " << m.final_pos << std::endl;
        return false;
    }

    move.type = it->type;
    // std::cout << "matching moves" << *it << std::endl;

    performMove(move, player_color);

    _chess_board->render();  // rerender board

    return true;  // move was valid
}

/*
simulateLegality goes through all moves in the validMoves set and performs the move, then rechecks if the player is in check.
If the player is in check after the move, the move is not legal and is added to the return set.
*/
void Game::simulateLegality(Move move, Color player_color, std::unordered_set<Move>& valid_moves_out) {
    // Create copies of old board state
    // auto old_board = *_chess_board;
    Color opponent_color = player_color == Color::WHITE ? Color::BLACK : Color::WHITE;
    auto old_opponent_alive_pieces = _chess_board->getAlivePieces(opponent_color);
    auto initial = move.initial_pos;
    auto final = move.final_pos;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();

    // if a piece was captured
    Player& captured_player = player_color == Color::WHITE ? *_black : *_white;
    std::shared_ptr<Piece> captured_piece = final_square.getPiece();
    if (captured_piece != nullptr) {
        // store the piece that was captured
        _chess_board->removeDeadPiece(captured_piece);
    }

    // Move the piece
    performMove(move, player_color);

    // Check if player is in check
    bool in_check;
    if (player_color == Color::WHITE) {
        in_check = _white->inCheck();
    } else {
        in_check = _black->inCheck();
    }

    // If still in check, move is not legal
    if (!in_check) {
        valid_moves_out.insert(move);
    }

    std::cout << move << std::endl;

    // Restore old board state depending on the type of move
    if (move.type == MoveType::KING_SIDE_CASTLE || move.type == MoveType::QUEEN_SIDE_CASTLE) {
        // undo rook (king will be handled later)
        Position rook_init = {initial.r, move.type == MoveType::KING_SIDE_CASTLE ? 7 : 0};
        Position rook_final = {initial.r, move.type == MoveType::KING_SIDE_CASTLE ? 5 : 3};
        Square& rook_init_square = _chess_board->getSquare(rook_init);
        Square& rook_final_square = _chess_board->getSquare(rook_final);

        if (rook_final_square.getPiece() == nullptr) {
            _chess_board->render();
            std::cout << "wtf" << std::endl;
        }

        rook_init_square.setPiece(rook_final_square.getPiece(), false);
        rook_init_square.getPiece()->setSquare(_chess_board->getSquarePtr(rook_init));
        rook_final_square.disconnectPiece();
        rook_init_square.getPiece()->Moved(false);
        _chess_board->render();
    }

    init_square.setPiece(piece_at_init, false);
    final_square.disconnectPiece();
    if (captured_piece != nullptr) final_square.setPiece(captured_piece, false);
    piece_at_init->setSquare(_chess_board->getSquarePtr(initial));
    _chess_board->setAlivePieces(old_opponent_alive_pieces, opponent_color);
    piece_at_init->Moved(false);
}

void Game::renderBoard() const {
    _chess_board->render();
}

void Game::reverseMoves(int n) {
}

Player& Game::getWhite() const {
    return *_white;
}

Player& Game::getBlack() const {
    return *_black;
}
