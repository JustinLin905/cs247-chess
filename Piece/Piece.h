#ifndef PIECE_H
#define PIECE_H

#include <memory>

#include "../enums.h"

class Square;
class Player;

class Piece {
 protected:
  std::unique_ptr<Square> _square;
  std::shared_ptr<Player> _player;
  Color _color;

 public:
  Piece(Color color, std::shared_ptr<Player> player);
  // std::unordered_set<Move> getValidMoves() const;
  virtual char getPieceChar() const = 0;
  virtual ~Piece() = default;
};

#endif
