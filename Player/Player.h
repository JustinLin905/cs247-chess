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
    Color _color;
    std::shared_ptr<Game> _game;
    std::weak_ptr<King> _king;

   public:
    Player(Color color);
    void resign();
    std::vector<Move> getValidPlayerMoves();
    bool inCheck() const;
    virtual Move getMove() = 0;
    void removeDeadPiece(std::shared_ptr<Piece> piece);
    void setKing(std::weak_ptr<King> king);
};

#endif