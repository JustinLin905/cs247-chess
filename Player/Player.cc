#include "Player.h"

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Piece/Piece.h"

Player::Player(Color color, std::shared_ptr<Game> game) : _color(color), _game{game} {}

void Player::addAlivePiece(Piece* piece) {
    _alive_pieces.emplace_back(piece);
}

void Player::resign() {
    Manager::closeGame();
}

/*
This method is to check whether or not a player has any more available moves to make.
This is used to check for checks and stalemates
*/
bool Player::hasValidMove() const {
    for(auto p : _alive_pieces) {
        if (p->getValidMoves().size() > 0) return true;
    }

    return false;
}