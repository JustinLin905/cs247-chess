#include "Position.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, Position& pos) {
    out << char(pos.c + 97) << pos.r;
    return out;
}
