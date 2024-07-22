#ifndef PIECE_H
#define PIECE_H

#include <memory>

class Square;
class Player;

class Piece {
  std::unique_ptr<Square> _square;
  std::shared_ptr<Player> _player;

 public:
  bool temp() const;
  // std::unordered_set<Move> getValidMoves() const;
  virtual char getPieceChar() const = 0;
};

#endif
