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

    // Check current player is in check
    bool in_check;
    if (player_color == Color::WHITE) {
        in_check = _white->inCheck();
        if (in_check) {
            std::cout << "White is in check" << std::endl;
        }
    } else if (_black->inCheck()) {
        in_check = _black->inCheck();
        if (in_check) {
            std::cout << "Black is in check" << std::endl;
        }
    }

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();
    if (piece_at_init == nullptr) return false;
    if (piece_at_init->getColor() != player_color) return false;

    std::unordered_set<Move> valid_moves = piece_at_init->getValidMoves();
    std::unordered_set<Move> valid_moves_during_check;

    if (in_check) {
        // If player is in check, simulate all moves to see if any move gets player out of check
        // This removes all moves that do not get player out of check
        for (auto it = valid_moves.begin(); it != valid_moves.end();) {
            simulateLegality(*it, player_color, valid_moves_during_check);
            it++;
        }
    } else {
        valid_moves_during_check = valid_moves;
    }

    if (valid_moves_during_check.empty()) {
        std::cout << "No legal moves for this piece!" << std::endl;
        return false;
    }

    // If move is not in the piece's valid moves, return false
    if (valid_moves_during_check.find(move) == valid_moves_during_check.end()) {
        std::cout << "Not found in legal moves. Legal moves for this piece: " << std::endl;
        for (auto m : piece_at_init->getValidMoves()) std::cout << m.initial_pos.c << m.initial_pos.r << " -> " << m.final_pos.c << m.final_pos.r << std::endl;
        return false;
    }

    // if a piece was captured
    if (final_square.getPiece() != nullptr) {
        Player& captured_player = player_color == Color::WHITE ? *_black : *_white;
        captured_player.removeDeadPiece(final_square.getPiece());
    }

    // Move the piece
    init_square.disconnectPiece();
    final_square.setPiece(piece_at_init, false);
    piece_at_init->setSquare(_chess_board->getSquarePtr(final));

    // update attack map
    _chess_board->updateAttackMap();
    _chess_board->render();  // rerender board

    return true;  // move was valid
}

/*
simulateLegality goes through all moves in the validMoves set and performs the move, then rechecks if the player is in check.
If the player is in check after the move, the move is not legal and is added to the return set.
*/
void Game::simulateLegality(Move move, Color player_color, std::unordered_set<Move>& valid_moves_during_check) {
    // Create copies of old board state
    // auto old_board = *_chess_board;
    auto old_opponent_alive_pieces = player_color == Color::WHITE ? _black->getAlivePieces() : _white->getAlivePieces();

    auto initial = move.initial_pos;
    auto final = move.final_pos;

    Square& init_square = _chess_board->getSquare(initial);
    Square& final_square = _chess_board->getSquare(final);

    auto piece_at_init = init_square.getPiece();

    // if a piece was captured
    Player& captured_player = player_color == Color::WHITE ? *_black : *_white;
    if (final_square.getPiece() != nullptr) {
        captured_player.removeDeadPiece(final_square.getPiece());
    }

    // Move the piece
    init_square.disconnectPiece();
    final_square.setPiece(piece_at_init, false);
    piece_at_init->setSquare(_chess_board->getSquarePtr(final));

    _chess_board->updateAttackMap();

    // Check if player is in check
    bool in_check;
    if (player_color == Color::WHITE) {
        in_check = _white->inCheck();
    } else {
        in_check = _black->inCheck();
    }

    // If still in check, move is not legal
    if (!in_check) {
        valid_moves_during_check.insert(move);
    }

    // Restore old board state
    init_square.setPiece(piece_at_init, false);
    final_square.disconnectPiece();
    piece_at_init->setSquare(_chess_board->getSquarePtr(initial));
    captured_player.setAlivePieces(old_opponent_alive_pieces);
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
