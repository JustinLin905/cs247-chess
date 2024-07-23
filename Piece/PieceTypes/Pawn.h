#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Pawn final : public Piece {
 public:
  Pawn(Color color, std::shared_ptr<Player> player,
       std::shared_ptr<ChessBoard> board);
  char getPieceChar() const override;
  std::unordered_set<Position> getAttackedSquares() const override;
  ~Pawn() = default;
};