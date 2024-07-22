#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "../Piece/Piece.h"
#include "../Position/Position.h"
#include "../enums.h"

class Square {
  Position _position;
  std::unique_ptr<Piece> _piece;

 public:
  Square() = default;
  Square(Position position);
  void setPosition(Position position);
  void setPiece(std::unique_ptr<Piece> piece);
  bool isEmpty() const;
  bool isAttacked(Color color) const;
  char getState() const;
};

#endif