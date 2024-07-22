#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>

#include "../enums.h"

class Player {
  std::vector<std::unique_ptr<Piece>> _alive_pieces;
  Color _color;

 public:
  void resign();
  // std::vector<Moves> getValidPlayerMoves();
  // virtual Move getMove() = 0;
};

#endif