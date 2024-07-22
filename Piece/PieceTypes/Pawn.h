#include "../../ChessBoard/Square.h"
#include "../Piece.h"
#include "../../Player/Player.h"

class Pawn final : public Piece {
 public:
  char getPieceChar() const override;
  ~Pawn() = default;
};