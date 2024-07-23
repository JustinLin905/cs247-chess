#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Queen final : public Piece {
 public:
  Queen(Color color, std::shared_ptr<Player> player);
  char getPieceChar() const override;
  ~Queen() = default;
};