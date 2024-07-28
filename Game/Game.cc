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
            return std::make_unique<HumanPlayer>(Color::WHITE, std::shared_ptr<Game>(this));
        case PlayerType::Type::COMPUTER_LEVEL1:
            return std::make_unique<ComputerLevel1>(Color::WHITE, std::shared_ptr<Game>(this));
        default:
            throw std::invalid_argument("Invalid player type");
    }
}

void Game::initDefaultGame() {
    _chess_board->defaultSetup(_white, _black, _chess_board);
}

bool Game::makeTurn(Move move, Color player_color) {
    auto initial = move.initial_pos;
    auto final = move.final_pos;
    std::cout << initial << std::endl;
    std::cout << final << std::endl;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();
    if (piece_at_init == nullptr) return false;
    if (piece_at_init->getColor() != player_color) return false;

    auto valid_moves = piece_at_init->getValidMoves();
    auto compare_moves = [initial, final](Move m) { return m.initial_pos == initial && m.final_pos == final; };
    auto it = std::find_if(valid_moves.begin(), valid_moves.end(), compare_moves);

    // If move is not in the piece's valid moves, return false
    if (it == valid_moves.end()) {
        std::cout << "Not found in legal moves. Legal moves for this piece: " << std::endl;
        for (auto m : valid_moves) std::cout << m.initial_pos.c << m.initial_pos.r << " -> " << m.final_pos.c << m.final_pos.r << std::endl;
        return false;
    }

    // check if move is castle
    char king_char = player_color == Color::WHITE ? 'K' : 'k';
    if (piece_at_init->getPieceChar() == king_char && (it->type == MoveType::KING_SIDE_CASTLE || it->type == MoveType::QUEEN_SIDE_CASTLE) && !piece_at_init->hasMoved()) {
        auto castle_type = it->type;
        Position rook_init = {initial.r, castle_type == MoveType::KING_SIDE_CASTLE ? 7 : 0};
        Position rook_final = {initial.r, castle_type == MoveType::KING_SIDE_CASTLE ? 5 : 3};
        Square& rook_init_square = _chess_board->getSquare(rook_init);
        Square& rook_final_square = _chess_board->getSquare(rook_final);
        auto rook = rook_init_square.getPiece();
        rook_init_square.disconnectPiece();
        rook_final_square.setPiece(rook, false);
        rook->setSquare(_chess_board->getSquarePtr(rook_final));
    }
    // if a piece was captured
    else if (final_square.getPiece() != nullptr) {
        Player& captured_player = player_color == Color::WHITE ? *_black : *_white;
        captured_player.removeDeadPiece(final_square.getPiece());
    }

    // Move the piece
    init_square.disconnectPiece();
    final_square.setPiece(piece_at_init, false);
    piece_at_init->setSquare(_chess_board->getSquarePtr(final));

    // mark the piece as moved
    piece_at_init->Moved();

    // update attack map
    _chess_board->updateAttackMap();
    _chess_board->render();  // rerender board
    return true;             // move was valid
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
