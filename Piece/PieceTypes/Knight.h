#ifndef KNIGHT_H
#define KNIGHT_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Knight final : public Piece {
 public:
  Knight(Color color, std::shared_ptr<Player> player,
         std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square);
  char getPieceChar() const override;
  std::unordered_set<Position> getAttackedSquares() const override;
  ~Knight() = default;
};

#endif