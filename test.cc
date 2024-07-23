#include "ChessBoard/ChessBoard.h"
#include "ObserverPattern/TextObserver.h"

int main() {
  std::shared_ptr<ChessBoard> board = std::make_shared<ChessBoard>();
  TextObserver text_observer(board, std::cout);
  board->defaultSetup();
  board->render();

  // Try to get attacked squares of a pawn
  Position pawn_pos{6, 1};
  if (board->getSquare(pawn_pos).getPiece() == nullptr) {
    std::cerr << "No piece found at " << pawn_pos.r << " " << pawn_pos.c
              << std::endl;
    return 1;
  }
  if (board->getSquare(pawn_pos).getPiece()->getPieceChar() != 'P') {
    std::cerr << "Piece at " << pawn_pos.r << " " << pawn_pos.c
              << " is not a pawn" << std::endl;
    return 1;
  }
  std::unordered_set<Position> pawn_attacked_squares =
      board->getSquare(pawn_pos).getPiece()->getAttackedSquares();

  for (const Position& pos : pawn_attacked_squares) {
    std::cout << pos.r << " " << pos.c << " attacked!" << std::endl;
  }
  return 0;
}