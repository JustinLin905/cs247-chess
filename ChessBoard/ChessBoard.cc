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
  // Thought: we will need to be able to reverse this based on the current
  // player's color
  reset();
  for (int i = 0; i < 8; i++) {
    // Need to update to set Player pointers correctly, instead of to nullptr
    _board[1][i].setPiece(std::make_unique<Pawn>(
        Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
    _board[6][i].setPiece(std::make_unique<Pawn>(
        Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  }
  _board[0][0].setPiece(std::make_unique<Rook>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][1].setPiece(std::make_unique<Knight>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][2].setPiece(std::make_unique<Bishop>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][3].setPiece(std::make_unique<Queen>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][4].setPiece(std::make_unique<King>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][5].setPiece(std::make_unique<Bishop>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][6].setPiece(std::make_unique<Knight>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[0][7].setPiece(std::make_unique<Rook>(
      Color::BLACK, nullptr, std::shared_ptr<ChessBoard>(this)));

  _board[7][0].setPiece(std::make_unique<Rook>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][1].setPiece(std::make_unique<Knight>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][2].setPiece(std::make_unique<Bishop>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][3].setPiece(std::make_unique<Queen>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][4].setPiece(std::make_unique<King>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][5].setPiece(std::make_unique<Bishop>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][6].setPiece(std::make_unique<Knight>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
  _board[7][7].setPiece(std::make_unique<Rook>(
      Color::WHITE, nullptr, std::shared_ptr<ChessBoard>(this)));
}

char ChessBoard::getState(int row, int col) const {
  return _board[row][col].getState();
}

Square &ChessBoard::getSquare(Position position) {
  return _board[position.r][position.c];
}

void ChessBoard::render() { notifyObservers(); }
