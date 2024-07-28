#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "../Game/Game.h"
#include "../Move/Move.h"
#include "../Piece/Piece.h"
#include "../enums.h"

class Piece;
class Game;

class Player {
   protected:
    Color _color;
    std::shared_ptr<Game> _game;

   public:
    std::vector<std::shared_ptr<Piece>> _alive_pieces;  // temporary public for testing

    Player(Color color, std::shared_ptr<Game> game);
    void resign();
    std::vector<Move> getValidPlayerMoves();
    bool hasValidMove() const;
    virtual Move getMove() = 0;
    void addAlivePiece(std::shared_ptr<Piece> piece);
    void removeDeadPiece(std::shared_ptr<Piece> piece);
};

#endif