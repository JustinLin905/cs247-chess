#include "ChessBoard.h"

ChessBoard::ChessBoard() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      _board[i][j].setPosition(Position{i, j});
    }
  }
}

void ChessBoard::reset() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      // needs implementation to move pieces to their initial positions
    }
  }
}

void ChessBoard::defaultSetup() {
  reset();
  for (int i = 0; i < 8; i++) {
    // Need to update to set Player pointers correctly, instead of to nullptr
    _board[1][i].setPiece(std::make_unique<Pawn>(Color::WHITE, nullptr));
    _board[6][i].setPiece(std::make_unique<Pawn>(Color::BLACK, nullptr));
  }
  // _board[0][0] = 'r';
  // _board[0][1] = 'n';
  // _board[0][2] = 'b';
  // _board[0][3] = 'q';
  // _board[0][4] = 'k';
  // _board[0][5] = 'b';
  // _board[0][6] = 'n';
  // _board[0][7] = 'r';
  // _board[7][0] = 'R';
  // _board[7][1] = 'N';
  // _board[7][2] = 'B';
  // _board[7][3] = 'Q';
  // _board[7][4] = 'K';
  // _board[7][5] = 'B';
  // _board[7][6] = 'N';
  // _board[7][7] = 'R';
}

char ChessBoard::getState(int row, int col) const {
  return _board[row][col].getState();
}

void ChessBoard::render() { notifyObservers(); }
