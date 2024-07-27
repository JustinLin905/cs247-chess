#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "../Piece/Piece.h"
#include "../Position/Position.h"
#include "../enums.h"

class Square {
    Position _position;
    std::unique_ptr<Piece> _piece = nullptr;

   public:
    Square() = default;
    Square(Position position);
    void setPosition(Position position);
    Position getPosition() const;
    std::unique_ptr<Piece> setPiece(std::unique_ptr<Piece> piece);
    Piece *getPiece() const;
    bool isEmpty() const;
    bool isAttacked(Color color) const;
    char getState() const;
};

#endif