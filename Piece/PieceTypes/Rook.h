#ifndef ROOK_H
#define ROOK_H

#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Rook final : public Piece {
    void getCastleMoves(std::unordered_set<Move>& moves, Position current_pos) const;

   public:
    Rook(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    std::unordered_set<Move> getValidMoves() const override;
    ~Rook() = default;
};

#endif