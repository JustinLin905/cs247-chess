#ifndef PAWN_H
#define PAWN_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Pawn final : public Piece {
    void getEnPassantMoves(std::unordered_set<Move>& moves, Position current_pos) const;

   public:
    Pawn(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    std::unordered_set<Move> getValidMoves() const override;
    bool movedTwoPreviously() const;
    ~Pawn() = default;
};

#endif