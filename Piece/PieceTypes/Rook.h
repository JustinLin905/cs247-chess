#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Rook final : public Piece {
 public:
  Rook(Color color, std::shared_ptr<Player> player);
  char getPieceChar() const override;
  ~Rook() = default;
};