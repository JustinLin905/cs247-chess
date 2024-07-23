#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class King final : public Piece {
 public:
  King(Color color, std::shared_ptr<Player> player);
  char getPieceChar() const override;
  std::unordered_set<Position> getAttackedSquares() const override;
  ~King() = default;
};