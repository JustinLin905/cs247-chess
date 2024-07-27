#include "Player.h"

#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Piece/Piece.h"

Player::Player(Color color, std::shared_ptr<Game> game) : _color(color), _game{game} {}

void Player::addAlivePiece(std::shared_ptr<Piece> piece) {
    _alive_pieces.insert(piece);
}

std::unordered_set<Move> Player::getValidPlayerMoves() {
    std::unordered_set<Move> validPlayerMoves;

    for(auto p : _alive_pieces) {
        std::unordered_set<Move> pieceValidMoves = p->getValidMoves();
        validPlayerMoves.insert(pieceValidMoves.begin(), pieceValidMoves.end());
    }

    return validPlayerMoves;
}

void Player::resign() {
    Manager::closeGame();
}