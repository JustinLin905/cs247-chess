#include "TextObserver.h"

#include "../ChessBoard/ChessBoard.h"

TextObserver::TextObserver(std::shared_ptr<ChessBoard> chess_board,
                           std::ostream &out)
    : _chess_board{chess_board}, _out{out} {
    _chess_board->attach(std::shared_ptr<TextObserver>(this));
}

void TextObserver::notify() {
    _out << "   ";
    for (int i = 0; i < 8; i++) {
        _out << char(65+i) << " ";
    }
    _out << std::endl;

    _out << "   ";
    for (int i = 0; i < 8; i++) {
        _out << "— ";
    }
    _out << std::endl;

    for (int i = 0; i < 8; i++) {
        _out << i << "| ";
        for (int j = 0; j < 8; j++) {
            _out << _chess_board->getState(i, j) << " ";
        }
        _out << std::endl;
    }
    _out << std::endl;
}
