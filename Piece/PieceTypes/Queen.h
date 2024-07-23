#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Queen final : public Piece {
 public:
  Queen(Color color, std::shared_ptr<Player> player,
        std::shared_ptr<ChessBoard> board);
  char getPieceChar() const override;
  std::unordered_set<Position> getAttackedSquares() const override;
  ~Queen() = default;
};