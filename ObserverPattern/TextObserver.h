#ifndef TEXT_OBSERVER_H
#define TEXT_OBSERVER_H
#include <cctype>
#include <iostream>
#include <memory>

// #include "../ChessBoard/ChessBoard.h"
#include "Observer.h"

class ChessBoard;

class TextObserver : public Observer {
    std::weak_ptr<ChessBoard> _chess_board;
    std::ostream &_out;

   public:
    TextObserver(std::weak_ptr<ChessBoard> chess_board, std::ostream &out);
    ~TextObserver() = default;
    void notify() override;
};

#endif
