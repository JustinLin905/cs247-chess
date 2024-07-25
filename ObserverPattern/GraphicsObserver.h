#ifndef _GRAPHICS_OBSERVER_H_
#define _GRAPHICS_OBSERVER_H_
#include <unordered_set>

#include "../ChessBoard/ChessBoard.h"
#include "Observer.h"
#include "window.h"

class GraphicsObserver : public Observer {
  std::shared_ptr<ChessBoard> _chess_board;
  Xwindow *_w;

 public:
  GraphicsObserver(std::shared_ptr<ChessBoard> chess_board);
  ~GraphicsObserver();
  void notify() override;
};

#endif
