#ifndef SQUARE_H
#define SQUARE_H

#include <memory>

#include "../Position/Position.h"
#include "../enums.h"
#include "../Piece/Piece.h"

class Square {
  Position _position;
  std::unique_ptr<Piece> _piece;

 public:
  Square(Position position);
  void setPiece(std::unique_ptr<Piece> piece);
  bool isEmpty() const;
  bool isAttacked(Color color) const;
  char getState() const;
};

#endif