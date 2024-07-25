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
    std::cout << pos.r << " " << pos.c << " attacked by pawn!" << std::endl;
  }

  // Test rook attacked squares
  Position rook_pos{7, 7};
  if (board->getSquare(rook_pos).getPiece() == nullptr) {
    std::cerr << "No piece found at " << rook_pos.r << " " << rook_pos.c
              << std::endl;
    return 1;
  }
  if (board->getSquare(rook_pos).getPiece()->getPieceChar() != 'R') {
    std::cerr << "Piece at " << rook_pos.r << " " << rook_pos.c
              << " is not a rook" << std::endl;
    return 1;
  }
  std::unordered_set<Position> rook_attacked_squares =
      board->getSquare(rook_pos).getPiece()->getAttackedSquares();

  for (const Position& pos : rook_attacked_squares) {
    std::cout << pos.r << " " << pos.c << " attacked by rook!" << std::endl;
  }

  // Test queen attacked squares
  std::cout << "Testing queen attacked squares" << std::endl;
  Position queen_pos{4, 3};
  if (board->getSquare(queen_pos).getPiece() == nullptr) {
    std::cerr << "No piece found at " << queen_pos.r << " " << queen_pos.c
              << std::endl;
    return 1;
  }
  if (board->getSquare(queen_pos).getPiece()->getPieceChar() != 'Q') {
    std::cerr << "Piece at " << queen_pos.r << " " << queen_pos.c
              << " is not a queen" << std::endl;
    return 1;
  }
  std::unordered_set<Position> queen_attacked_squares =
      board->getSquare(queen_pos).getPiece()->getAttackedSquares();

  for (const Position& pos : queen_attacked_squares) {
    std::cout << pos.r << " " << pos.c << " attacked by queen!" << std::endl;
  }

  return 0;
}