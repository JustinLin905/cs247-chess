#ifndef ROOK_H
#define ROOK_H

#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Rook final : public Piece {
   public:
    Rook(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    std::unordered_set<Move> getValidMoves() const override;
    ~Rook() = default;
};

#endif