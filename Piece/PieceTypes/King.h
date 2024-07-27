#ifndef KING_H
#define KING_H

#include "../../ChessBoard/ChessBoard.h"
#include "../../ChessBoard/Square.h"
#include "../../Player/Player.h"
#include "../Piece.h"

class King final : public Piece {
   public:
    King(Color color, Player* player,
         std::shared_ptr<ChessBoard> board, std::weak_ptr<Square> square);
    char getPieceChar() const override;
    std::unordered_set<Position> getAttackedSquares() const override;
    bool inCheck() const;
    ~King() = default;
};

#endif