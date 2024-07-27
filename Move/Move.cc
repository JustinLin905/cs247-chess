#include "Move.h"
#include "../Position/Position.h"
#include <iostream>

std::ostream& operator<<(std::ostream& out, Move& move) {
    out << "Initial: " << move.initial_pos << ", Final: " << move.final_pos << ", Move Type: " << static_cast<int>(move.type);
    return out;
}
