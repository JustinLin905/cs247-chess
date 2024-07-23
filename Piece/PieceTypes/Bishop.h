#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Bishop final : public Piece {
 public:
  Bishop(Color color, std::shared_ptr<Player> player);
  char getPieceChar() const override;
  std::unordered_set<Position> getAttackedSquares() const override;
  ~Bishop() = default;
};