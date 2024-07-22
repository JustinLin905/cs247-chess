#ifndef MOVE_H
#define MOVE_H

#include "../Move/MoveType.h"
#include "../Position/Position.h"

struct Move {
    Position initial_pos;
    Position final_pos;
    MoveType type;

    Move(Position initial_pos, Position final_pos, MoveType type = MoveType::UNDETERMINED) : initial_pos(initial_pos), final_pos(final_pos), type(type) {}
};

#endif