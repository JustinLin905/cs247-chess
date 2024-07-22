#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../ObserverPattern/Subject.h"
#include "Square.h"

class ChessBoard : public Subject {
  std::array<std::array<Square, 8>, 8> _board;

 public:
  ChessBoard();
  char getState(int row, int col) const;
  void render();
  void defaultSetup();
  // void customSetup();
  void reset();
};

#endif