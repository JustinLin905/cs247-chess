#ifndef PAWN_H
#define PAWN_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Pawn final : public Piece {
 public:
  Pawn(Color color, Player* player,
       std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square);
  char getPieceChar() const override;
  std::unordered_set<Position> getAttackedSquares() const override;
  std::unordered_set<Move> getValidMoves() const override;
  ~Pawn() = default;
};

#endif