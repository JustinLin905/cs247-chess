#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "../Piece/Piece.h"
#include "../Position/Position.h"
#include "../enums.h"

class Square {
    Position _position;
    std::weak_ptr<Piece> _piece;

   public:
    Square() = default;
    Square(Position position);
    void setPosition(Position position);
    Position getPosition() const;
    void setPiece(std::weak_ptr<Piece> piece, bool isNew = true);
    std::shared_ptr<Piece> getPiece() const;
    void disconnectPiece();
    bool isEmpty() const;
    bool isAttacked(Color color) const;
    char getState() const;
};

#endif