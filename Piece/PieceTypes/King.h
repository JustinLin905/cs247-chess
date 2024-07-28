#ifndef KING_H
#define KING_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
// #include "../../Player/Player.h"
#include "../Piece.h"

class Player;

class King final : public Piece {
    void getCastleMoves(std::unordered_set<Move>& moves, Position current_pos) const;

   public:
    King(Color color, Player* player, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    std::unordered_set<Move> getValidMoves() const override;
    bool inCheck() const;
    ~King() = default;
};

#endif