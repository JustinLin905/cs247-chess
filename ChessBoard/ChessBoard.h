#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include "../ObserverPattern/Subject.h"

class ChessBoard : public Subject {
  std::array<std::array<char, 8>, 8> _board;

 public:
  ChessBoard();
  char getState(int row, int col) const;
  void render();
  void defaultSetup();
  // void customSetup();
  void reset();
};

#endif