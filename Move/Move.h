#ifndef MOVE_H
#define MOVE_H

#include "../Move/MoveType.h"
#include "../Position/Position.h"

struct Move {
    Position initial_pos;
    Position final_pos;
    MoveType type;

    Move(Position initial_pos, Position final_pos, MoveType type = MoveType::UNDETERMINED) : initial_pos(initial_pos), final_pos(final_pos), type(type) {}

    bool operator==(const Move &other) const {
        return initial_pos == other.initial_pos && final_pos == other.final_pos && type == other.type;
    }

    bool operator!=(const Move &other) const { return !(*this == other); }

};

// Hash function for Move
namespace std {
    template <>
    struct hash<Move> {
        size_t operator()(const Move &move) const {
            size_t h1 = std::hash<Position>()(move.initial_pos);
            size_t h2 = std::hash<Position>()(move.final_pos);
            size_t h3 = std::hash<int>()(static_cast<int>(move.type));
            return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine using XOR and shifts
        }
    };
}

#endif