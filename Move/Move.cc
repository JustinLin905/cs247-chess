#include "Move.h"

#include <iostream>

#include "../Position/Position.h"

std::ostream& operator<<(std::ostream& out, Move& move) {
    out << "Initial: " << move.initial_pos << ", Final: " << move.final_pos << ", Move Type: " << static_cast<int>(move.type);
    return out;
}

std::ostream& operator<<(std::ostream& out, const Move& move) {
    out << "Initial: " << move.initial_pos << ", Final: " << move.final_pos << ", Move Type: " << static_cast<int>(move.type);
    return out;
}
