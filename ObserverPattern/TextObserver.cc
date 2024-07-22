#include "TextObserver.h"

#include "Subject.h"

TextObserver::TextObserver(std::shared_ptr<ChessBoard> chess_board,
                           std::ostream &out)
    : _chess_board{chess_board}, _out{out} {
  _chess_board->attach(std::make_unique<TextObserver>(*this));
}

void TextObserver::notify() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      _out << _chess_board->getState(i, j) << " ";
    }
    _out << std::endl;
  }
  _out << std::endl;
}
