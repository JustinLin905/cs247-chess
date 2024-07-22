#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Knight final : public Piece {
 public:
  Knight(Color color, std::shared_ptr<Player> player);
  char getPieceChar() const override;
  ~Knight() = default;
};