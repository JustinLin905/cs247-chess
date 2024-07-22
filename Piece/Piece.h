#ifndef PIECE_H
#define PIECE_H

#include <memory>

#include "../ChessBoard/Square.h"
#include "../Player/Player.h"

class Piece {
  std::unique_ptr<Square> _square;
  std::shared_ptr<Player> _player;

 public:
  // std::unordered_set<Move> getValidMoves() const;
  virtual char getPieceChar() const = 0;
};

#endif
