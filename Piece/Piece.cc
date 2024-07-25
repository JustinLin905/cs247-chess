#include "Piece.h"

#include "../ChessBoard/ChessBoard.h"
#include "../ChessBoard/Square.h"
#include "../Player/Player.h"

Piece::Piece(Color color, std::shared_ptr<Player> player,
             std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square)
    : _color(color), _player(player), _board(board), _square(square) {}

Color Piece::getColor() const { return _color; }

/*
tryAttackSquare is a helper function that checks if a square can be attacked by
this piece. Handles bounds checking and opposing color checking.

Returns true if the loop using this function should continue searching in this
direction, false otherwise.
*/
bool Piece::tryAttackSquare(
    Position pos, std::unordered_set<Position>& attacked_squares) const {
  if (pos.r < 0 || pos.r >= 8 || pos.c < 0 || pos.c >= 8) {
    return false;
  }

  if (_board == nullptr) {
    std::cerr << "Error: Board is null" << std::endl;
    return false;
  }

  if (_board->getSquare(pos).isEmpty()) {
    attacked_squares.insert(pos);
    return true;
  } else {
    if (_board->getSquare(pos).getPiece()->getColor() != _color) {
      attacked_squares.insert(pos);
    }
    return false;
  }
}

/*
Methods to handle attacking diagonally.

Re-used by Bishop and Queen.
*/
void Piece::attackDiagonal(
    std::unordered_set<Position>& attacked_squares) const {
  Position current_pos = _square->getPosition();

  // Check all diagonals
  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{current_pos.r + i, current_pos.c + i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{current_pos.r - i, current_pos.c - i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{current_pos.r + i, current_pos.c - i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }

  for (int i = 1; i < 8; i++) {
    Position next_pos = Position{current_pos.r - i, current_pos.c + i};
    if (!tryAttackSquare(next_pos, attacked_squares)) {
      break;
    }
  }
}

/*
Methods to handle attacking straight.

Re-used by Rook and Queen.
*/
void Piece::attackStraight(
    std::unordered_set<Position>& attacked_squares) const {
  Position current_pos = _square->getPosition();
  int row = current_pos.r;
  int col = current_pos.c;

  // Check all squares to the right of the piece
  for (int i = col + 1; i < 8; i++) {
    if (!tryAttackSquare(Position{row, i}, attacked_squares)) {
      break;
    }
  }

  // Check all squares to the left of the piece
  for (int i = col - 1; i >= 0; i--) {
    if (!tryAttackSquare(Position{row, i}, attacked_squares)) {
      break;
    }
  }

  // Check all squares above the piece
  for (int i = row - 1; i >= 0; i--) {
    if (!tryAttackSquare(Position{i, col}, attacked_squares)) {
      break;
    }
  }

  // Check all squares below the piece
  for (int i = row + 1; i < 8; i++) {
    if (!tryAttackSquare(Position{i, col}, attacked_squares)) {
      break;
    }
  }
}
