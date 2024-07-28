#ifndef QUEEN_H
#define QUEEN_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Queen final : public Piece {
   public:
    Queen(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    ~Queen() = default;
};

#endif