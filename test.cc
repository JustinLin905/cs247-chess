#include "ChessBoard/ChessBoard.h"
#include "ObserverPattern/TextObserver.h"

int main() {
  std::shared_ptr<ChessBoard> board = std::make_shared<ChessBoard>();
  TextObserver text_observer(board, std::cout);
  board->defaultSetup();
  board->render();
  return 0;
}