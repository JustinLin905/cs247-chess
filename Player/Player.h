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
    std::vector<Piece*> _alive_pieces;
    Color _color;
    std::shared_ptr<Game> _game;

   public:
    Player(Color color, std::shared_ptr<Game> game);
    void resign();
    std::vector<Move> getValidPlayerMoves();
    virtual Move getMove() = 0;
    void addAlivePiece(Piece* piece);
};

#endif