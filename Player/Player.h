#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "../Game/Game.h"
#include "../Move/Move.h"
#include "../Piece/Piece.h"
// #include "../Piece/PieceTypes/King.h"
#include "../enums.h"

class Piece;
class Game;
class King;

class Player {
   protected:
    std::vector<std::shared_ptr<Piece>> _alive_pieces;
    Color _color;
    std::shared_ptr<Game> _game;
    std::weak_ptr<King> _king;

   public:
    Player(Color color);
    void resign();
    std::vector<Move> getValidPlayerMoves();
    bool inCheck() const;
    bool hasValidMove() const;
    virtual Move getMove() = 0;
    void addAlivePiece(std::shared_ptr<Piece> piece);
    void setAlivePieces(std::vector<std::shared_ptr<Piece>> pieces);
    void removeDeadPiece(std::shared_ptr<Piece> piece);
    std::vector<std::shared_ptr<Piece>> getAlivePieces() const;
};

#endif