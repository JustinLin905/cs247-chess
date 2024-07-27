#ifndef BISHOP_H
#define BISHOP_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class Bishop final : public Piece {
   public:
    Bishop(Color color, Player* player,
           std::shared_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    ~Bishop() = default;
};

#endif