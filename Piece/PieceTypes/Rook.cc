#include "Rook.h"

#include "../../ChessBoard/ChessBoard.h"

Rook::Rook(Color color, std::shared_ptr<Player> player,
           std::shared_ptr<ChessBoard> board)
    : Piece(color, player, board) {}

char Rook::getPieceChar() const { return _color == Color::WHITE ? 'R' : 'r'; }

std::unordered_set<Position> Rook::getAttackedSquares() const {
  std::unordered_set<Position> attackedSquares;
  Position currentPos = _square->getPosition();
  int row = currentPos.r;
  int col = currentPos.c;

  // Check all squares to the right of the rook
  for (int i = col + 1; i < 8; i++) {
    if (_board->getSquare(Position{row, i}).isEmpty()) {
      attackedSquares.insert(Position{row, i});
    } else {
      if (_board->getSquare(Position{row, i}).getPiece()->getColor() !=
          _color) {
        attackedSquares.insert(Position{row, i});
      }
      break;
    }
  }

  // Check all squares to the left of the rook
  for (int i = col - 1; i >= 0; i--) {
    if (_board->getSquare(Position{row, i}).isEmpty()) {
      attackedSquares.insert(Position{row, i});
    } else {
      if (_board->getSquare(Position{row, i}).getPiece()->getColor() !=
          _color) {
        attackedSquares.insert(Position{row, i});
      }
      break;
    }
  }

  // Check all squares above the rook
  for (int i = row - 1; i >= 0; i--) {
    if (_board->getSquare(Position{i, col}).isEmpty()) {
      attackedSquares.insert(Position{i, col});
    } else {
      if (_board->getSquare(Position{i, col}).getPiece()->getColor() !=
          _color) {
        attackedSquares.insert(Position{i, col});
      }
      break;
    }
  }

  // Check all squares below the rook
  for (int i = row + 1; i < 8; i++) {
    if (_board->getSquare(Position{i, col}).isEmpty()) {
      attackedSquares.insert(Position{i, col});
    } else {
      if (_board->getSquare(Position{i, col}).getPiece()->getColor() !=
          _color) {
        attackedSquares.insert(Position{i, col});
      }
      break;
    }
  }

  return attackedSquares;
}