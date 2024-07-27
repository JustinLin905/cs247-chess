#include "Player.h"

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Piece/Piece.h"

Player::Player(Color color, std::shared_ptr<Game> game) : _color(color), _game{game} {}

void Player::addAlivePiece(std::shared_ptr<Piece> piece) {
    _alive_pieces.insert(piece);
}

bool Player::hasValidMove() {
    for(auto p : _alive_pieces) {
        if (p->getValidMoves().size() > 0) return true;
    }

    return false;
}

void Player::resign() {
    Manager::closeGame();
}