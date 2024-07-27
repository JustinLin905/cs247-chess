#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include <map>

#include "../ObserverPattern/Subject.h"
#include "../Piece/PieceTypes/Bishop.h"
#include "../Piece/PieceTypes/King.h"
#include "../Piece/PieceTypes/Knight.h"
#include "../Piece/PieceTypes/Pawn.h"
#include "../Piece/PieceTypes/Queen.h"
#include "../Piece/PieceTypes/Rook.h"
#include "Square.h"

class ChessBoard : public Subject {
    std::array<std::array<std::shared_ptr<Square>, 8>, 8> _board;
    std::map<Position, std::vector<std::weak_ptr<Piece>>> attack_map;

   public:
    ChessBoard();
    Square &getSquare(Position position);
    std::shared_ptr<Square> getSquarePtr(Position position);
    char getState(int row, int col) const;
    void render();
    void defaultSetup(std::unique_ptr<Player> &whitePlayer, std::unique_ptr<Player> &blackPlayer);
    void updateAttackMap();
    bool isPositionUnderAttack(Position position, Color color) const;
    // void customSetup();
    void reset();
};

#endif