#ifndef TEXT_OBSERVER_H
#define TEXT_OBSERVER_H
#include <iostream>
#include <memory>

#include "ChessBoard.h"
#include "observer.h"

class TextObserver : public Observer {
  std::shared_ptr<ChessBoard> _chess_board;
  std::ostream &_out;

 public:
  TextObserver(std::shared_ptr<ChessBoard> chess_board, std::ostream &out);
  ~TextObserver() = default;
  void notify() override;
};

#endif
