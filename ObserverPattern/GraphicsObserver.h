#ifndef _GRAPHICS_OBSERVER_H_
#define _GRAPHICS_OBSERVER_H_
#include <memory>
#include <unordered_set>
#include <vector>

#include "../Move/Move.h"
#include "Observer.h"
#include "window.h"

class ChessBoard;

class GraphicsObserver : public Observer {
    std::vector<std::vector<char>> prev_state;
    std::weak_ptr<ChessBoard> _chess_board;
    void drawPiece(char piece, int row, int col, bool isWhite);
    Xwindow *_w;

   public:
    GraphicsObserver(std::weak_ptr<ChessBoard> chess_board);
    ~GraphicsObserver();
    void notify() override;
    void render();
    void peek(Position pos);
};

#endif
