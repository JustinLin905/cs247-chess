#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Pawn final : public Piece {
 public:
  Pawn(Color color, std::shared_ptr<Player> player);
  char getPieceChar() const override;
  ~Pawn() = default;
};