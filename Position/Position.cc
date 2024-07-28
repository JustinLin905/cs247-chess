#include "Position.h"

#include <iostream>

std::ostream& operator<<(std::ostream& out, const Position& pos) {
    out << char(pos.c + 97) << pos.r;
    return out;
}

std::istream& operator>>(std::istream& in, Position& pos) {
    char col;
    int row;
    in >> col >> row;
    pos.c = (int)(col)-97;
    pos.r = row;

    return in;
}