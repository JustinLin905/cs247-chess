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
    std::shared_ptr<Square> _square;
    Player* _player;
    std::shared_ptr<ChessBoard> _board;
    Color _color;
    bool tryAttackSquare(Position pos,
                         std::unordered_set<Position>& attackedSquares) const;
    void attackDiagonal(std::unordered_set<Position>& attackedSquares) const;
    void attackStraight(std::unordered_set<Position>& attackedSquares) const;

   public:
    Piece(Color color, Player* player,
          std::shared_ptr<ChessBoard> board, std::shared_ptr<Square> square);
    virtual std::unordered_set<Position> getAttackedSquares() const = 0;
    virtual std::unordered_set<Move> getValidMoves() const;
    void setSquare(std::shared_ptr<Square> square);
    Color getColor() const;
    Player* getPlayer() const;
    virtual char getPieceChar() const = 0;
    virtual ~Piece() = default;
};

#endif
