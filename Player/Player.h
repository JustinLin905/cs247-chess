#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "../enums.h"

class Piece;

class Player {
  std::vector<std::shared_ptr<Piece>> _alive_pieces;
  Color _color;

 public:
  Player(Color color);
  void resign();
  // std::vector<Moves> getValidPlayerMoves();
  // virtual Move getMove() = 0;
};

#endif