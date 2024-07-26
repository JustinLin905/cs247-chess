#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "../Game/Game.h"
#include "../Move/Move.h"
#include "../Piece/Piece.h"
#include "../enums.h"

class Piece;

class Player {
   protected:
    std::vector<std::shared_ptr<Piece>> _alive_pieces;
    Color _color;
    Game _game;

   public:
    Player(Color color, Game &game);
    void resign();
    std::vector<Move> getValidPlayerMoves();
    virtual Move getMove() = 0;
};

#endif