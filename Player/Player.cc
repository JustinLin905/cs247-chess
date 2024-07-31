#include "Player.h"

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Piece/Piece.h"
#include "../Piece/PieceTypes/King.h"

Player::Player(Color color, std::weak_ptr<Game> game) : _color(color), _game(game) {}

void Player::setKing(std::weak_ptr<King> king) {
    _king = king;
}

void Player::resign() {
    if (_color == Color::WHITE) {
        std::cout << "Black wins!" << std::endl;
        Manager::getLeaderBoard().winBlack();
    } else {
        std::cout << "White wins!" << std::endl;
        Manager::getLeaderBoard().winWhite();
    }
    Manager::closeGame();
}

bool Player::inCheck() const {
    std::shared_ptr<King> king_shared = _king.lock();
    if (!king_shared) {
        std::cerr << "Error: King is null" << std::endl;
        return false;
    }

    return king_shared->inCheck();
}

Color Player::getColor() const {
    return _color;
}
