#include "Player.h"

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Piece/Piece.h"
#include "../Piece/PieceTypes/King.h"

Player::Player(Color color, std::shared_ptr<Game> game) : _color(color), _game{game} {}

void Player::addAlivePiece(std::shared_ptr<Piece> piece) {
    _alive_pieces.emplace_back(piece);

    if (piece->getPieceChar() == 'K' || piece->getPieceChar() == 'k') {
        _king = std::dynamic_pointer_cast<King>(piece);
    }
}

void Player::removeDeadPiece(std::shared_ptr<Piece> piece) {
    _alive_pieces.erase(std::remove(_alive_pieces.begin(), _alive_pieces.end(), piece), _alive_pieces.end());
}

void Player::resign() {
    Manager::closeGame();
}

/*
This method is to check whether or not a player has any more available moves to make.
This is used to check for checks and stalemates
*/
bool Player::hasValidMove() const {
    for (auto p : _alive_pieces) {
        if (p->getValidMoves().size() > 0) return true;
    }

    return false;
}

bool Player::inCheck() const {
    std::shared_ptr<King> king_shared = _king.lock();
    if (!king_shared) {
        std::cerr << "Error: King is null" << std::endl;
        return false;
    }

    return king_shared->inCheck();
}