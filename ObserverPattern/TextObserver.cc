#include "TextObserver.h"

#include "../ChessBoard/ChessBoard.h"

TextObserver::TextObserver(std::weak_ptr<ChessBoard> chess_board, std::ostream &out) : _chess_board{chess_board}, _out{out} {
    _chess_board.lock()->attach(this);
}

void TextObserver::notify() {
    _out << std::endl
         << "   ";
    for (int i = 0; i < 8; i++) {
        _out << char(65 + i) << " ";
    }
    _out << std::endl;

    _out << "   ";
    for (int i = 0; i < 8; i++) {
        _out << "— ";
    }
    _out << std::endl;

    for (int i = 0; i < 8; i++) {
        _out << 8 - i << "| ";
        for (int j = 0; j < 8; j++) {
            char state = _chess_board.lock()->getState(i, j);
            if (std::islower(state)) {
                _out << "\033[34m" << state << "\033[0m ";
            } else if (std::isupper(state)) {
                _out << "\033[36m" << state << "\033[0m ";
            } else {
                _out << state << " ";
            }
        }
        _out << std::endl;
    }
    _out << std::endl;
}
