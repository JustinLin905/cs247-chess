#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <memory>
#include <unordered_set>

#include "../Move/Move.h"
#include "../enums.h"

class Square;
class Player;
class ChessBoard;
struct Position;

class Piece {
   protected:
    bool _moved = false;
    std::weak_ptr<Square> _square;
    std::weak_ptr<ChessBoard> _board;
    Color _color;
    bool tryAttackSquare(Position pos, std::unordered_set<Position>& attackedSquares) const;
    void attackDiagonal(std::unordered_set<Position>& attackedSquares) const;
    void attackStraight(std::unordered_set<Position>& attackedSquares) const;

   public:
    Piece(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Square> square);

    virtual std::unordered_set<Position> getAttackedSquares() const = 0;
    virtual std::unordered_set<Move> getValidMoves() const;

    std::shared_ptr<Square> getSquare() const;
    void setSquare(std::weak_ptr<Square> square);

    Color getColor() const;
    virtual char getPieceChar() const = 0;

    void Moved(bool moved = true) { _moved = moved; }
    bool hasMoved() const { return _moved; }

    virtual ~Piece() = default;
};

#endif
