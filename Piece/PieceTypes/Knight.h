#ifndef KNIGHT_H
#define KNIGHT_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Knight final : public Piece {
   public:
    Knight(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    ~Knight() = default;
};

#endif