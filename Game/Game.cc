#include "Game.h"

#include <iostream>
#include <memory>

#include "../Player/ComputerPlayer/ComputerLevel1.h"
#include "../Player/ComputerPlayer/ComputerLevel2.h"
// #include "../Player/ComputerPlayer/ComputerLevel3.h"
// #include "../Player/ComputerPlayer/ComputerLevel4.h"
#include "../Player/HumanPlayer.h"
#include "../PlayerType/PlayerType.h"

Game::Game() : _chess_board(std::make_shared<ChessBoard>()),
               _text_observer{std::make_shared<TextObserver>(_chess_board, std::cout)},
               _graphics_observer{std::make_shared<GraphicsObserver>(_chess_board)} {}

void Game::setupPlayers(PlayerType::Type white, PlayerType::Type black) {
    _white = createPlayerPtr(white, Color::WHITE);
    _white->setKing(_chess_board->getKing(Color::WHITE));
    _black = createPlayerPtr(black, Color::BLACK);
    _black->setKing(_chess_board->getKing(Color::BLACK));
}

std::unique_ptr<Player> Game::createPlayerPtr(PlayerType::Type type, Color color) {
    switch (type) {
        case PlayerType::Type::HUMAN:
            return std::make_unique<HumanPlayer>(color);
        case PlayerType::Type::COMPUTER_LEVEL1:
            return std::make_unique<ComputerLevel1>(color, _chess_board);
        case PlayerType::Type::COMPUTER_LEVEL2:
            return std::make_unique<ComputerLevel2>(color, _chess_board);
        default:
            throw std::invalid_argument("Invalid player type");
    }
}

void Game::initDefaultGame() {
    _chess_board->defaultSetup(_chess_board);
}

void Game::setupBoard() {
    _chess_board->customSetup(_chess_board);
}

bool Game::anyValidMoves(Color player_color) {
    // Get all pieces of player color
    auto alive_pieces = _chess_board->getAlivePieces(player_color);

    // Get all valid moves for each piece
    for (auto piece : alive_pieces) {
        if (!piece->getValidMoves().empty()) return true;
    }

    return false;
}

void Game::performMove(Move move, Color player_color) {
    auto initial = move.initial_pos;
    auto final = move.final_pos;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    std::shared_ptr<Piece> moving_piece = init_square.getPiece();

    // if (moving_piece != nullptr) {
    //     std::cout << "Has " << moving_piece->getPieceChar() << " moved: " << moving_piece->hasMoved() << std::endl;
    // }

    // check if move is castle
    char king_char = player_color == Color::WHITE ? 'K' : 'k';
    char pawn_char = player_color == Color::WHITE ? 'P' : 'p';

    if (moving_piece->getPieceChar() == king_char && (move.type == MoveType::KING_SIDE_CASTLE || move.type == MoveType::QUEEN_SIDE_CASTLE) && !moving_piece->hasMoved()) {
        auto castle_type = move.type;
        Position rook_init = {initial.r, castle_type == MoveType::KING_SIDE_CASTLE ? 7 : 0};
        Position rook_final = {initial.r, castle_type == MoveType::KING_SIDE_CASTLE ? 5 : 3};
        Move rook_move = {rook_init, rook_final, MoveType::DEFAULT};

        // std::cout << "Has rook moved: " << _chess_board->getSquare(rook_init).getPiece()->hasMoved() << std::endl;

        performMove(rook_move, player_color);
    }
    // check if move is enpassant
    else if (moving_piece->getPieceChar() == pawn_char && move.type == MoveType::ENPASSANT) {
        Position captured_pawn_pos = {initial.r, final.c};
        _chess_board->removeDeadPiece(_chess_board->getSquare(captured_pawn_pos).getPiece());
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

bool Game::makeTurn(Move move, Color player_color, bool in_check) {
    auto initial = move.initial_pos;
    auto final = move.final_pos;
    // std::cout << initial << std::endl;
    // std::cout << final << std::endl;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();
    if (piece_at_init == nullptr) return false;
    if (piece_at_init->getColor() != player_color) return false;

    std::unordered_set<Move> valid_moves = piece_at_init->getValidMoves();

    if (valid_moves.empty()) {
        std::cout << "No legal moves for this piece!" << std::endl;
        return false;
    }

    // for comparing moves regardless of move type. We now determine the type of move the player wants to make
    auto compare_moves = [initial, final](Move m) { return m.initial_pos == initial && m.final_pos == final; };
    auto it = std::find_if(valid_moves.begin(), valid_moves.end(), compare_moves);

    // If move is not in the piece's valid moves, return false
    if (it == valid_moves.end()) {
        std::cout << "Not found in legal moves. Legal moves for this piece: " << std::endl;
        for (auto m : valid_moves) std::cout << m.initial_pos << " -> " << m.final_pos << std::endl;
        return false;
    }

    move.type = it->type;
    performMove(move, player_color);

    // Check for pawn promotion
    bool is_at_final_rank = final.r == 0 || final.r == 7;
    if ((piece_at_init->getPieceChar() == 'P' || piece_at_init->getPieceChar() == 'p') && is_at_final_rank) {
        std::shared_ptr<Pawn> pawn = std::dynamic_pointer_cast<Pawn>(piece_at_init);
        pawn->promote();
    }
    if (player_color == Color::WHITE)
        _white_moves.emplace_back(move);
    else
        _black_moves.emplace_back(move);

    // std::cout << "white move count: " << _white_moves.size() << std::endl;
    // std::cout << "black move count: " << _black_moves.size() << std::endl;

    _chess_board->render();  // rerender board

    return true;  // move was valid
}

/*
simulateLegality goes through all moves in the validMoves set and performs the move, then rechecks if the player is in check.
If the player is in check after the move, the move is not legal and is added to the return set.
*/
bool Game::simulateLegality(Move move, Color player_color) {
    bool valid = true;

    // Create copies of old board state
    // auto old_board = *_chess_board;
    Color opponent_color = player_color == Color::WHITE ? Color::BLACK : Color::WHITE;
    auto old_opponent_alive_pieces = _chess_board->getAlivePieces(opponent_color);
    auto initial = move.initial_pos;
    auto final = move.final_pos;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();
    auto piece_at_init_moved = piece_at_init->hasMoved();

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
    if (player_color == Color::WHITE)
        in_check = _white->inCheck();
    else
        in_check = _black->inCheck();

    // If still in check, move is not legal
    if (in_check) valid = false;

    // Restore old board state depending on the type of move ---------------------------------------------
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
        // _chess_board->render();
    } else if (move.type == MoveType::ENPASSANT) {
        // undo en passant
        Position captured_pawn_pos = {initial.r, final.c};
        _chess_board->getSquare(captured_pawn_pos).setPiece(captured_piece, false);
    }

    init_square.setPiece(piece_at_init, false);
    final_square.disconnectPiece();
    if (captured_piece != nullptr) final_square.setPiece(captured_piece, false);
    piece_at_init->setSquare(_chess_board->getSquarePtr(initial));
    _chess_board->setAlivePieces(old_opponent_alive_pieces, opponent_color);
    piece_at_init->Moved(piece_at_init_moved);
    _chess_board->updateAttackMap();

    return valid;
}

void Game::renderBoard() const {
    _chess_board->render();
}

void Game::reverseMoves(int n) {
}

Move Game::getLastMove(Color player_color) const {
    return player_color == Color::WHITE ? _white_moves.back() : _black_moves.back();
}

Player& Game::getWhite() const {
    return *_white;
}

Player& Game::getBlack() const {
    return *_black;
}

ChessBoard& Game::getChessBoard() const {
    return *_chess_board;
}

void Game::peek(Position pos, Color player_color) {
    if (_graphics_observer == nullptr) {
        throw std::invalid_argument("Graphics observer is not initialized");
    }

    if (_chess_board->getSquare(pos).getPiece() == nullptr) {
        std::cout << "No piece to peek at this position." << std::endl;
        return;
    }

    if (_chess_board->getSquare(pos).getPiece()->getColor() != player_color) {
        std::cout << "Cannot peek at opponent's piece!" << std::endl;
        return;
    }

    _graphics_observer->peek(pos);
}
