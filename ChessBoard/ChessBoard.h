#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>

#include "../ObserverPattern/Subject.h"
#include "../Piece/PieceTypes/Bishop.h"
#include "../Piece/PieceTypes/King.h"
#include "../Piece/PieceTypes/Knight.h"
#include "../Piece/PieceTypes/Pawn.h"
#include "../Piece/PieceTypes/Queen.h"
#include "../Piece/PieceTypes/Rook.h"
#include "Square.h"

class ChessBoard : public Subject {
    std::array<std::array<Square, 8>, 8> _board;

   public:
    ChessBoard();
    Square &getSquare(Position position);
    char getState(int row, int col) const;
    void render();
    void defaultSetup(std::unique_ptr<Player> &whitePlayer, std::unique_ptr<Player> &blackPlayer);
    // void customSetup();
    void reset();
};

#endif