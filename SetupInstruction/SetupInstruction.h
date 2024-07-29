#ifndef SETUP_INSTRUCTION_H
#define SETUP_INSTRUCTION_H

#include "../Position/Position.h"
#include "../enums.h"

enum class SetupCmds {
    CMD_ADD_PIECE,
    CMD_REMOVE_PIECE,
    CMD_SET_TURN,
    CMD_SETUP_DONE,
    CMD_UNKNOWN
};

struct SetupInstruction {
    SetupCmds cmd;
    char piece;
    Position pos;
    Color color;

    SetupInstruction(SetupCmds cmd, char piece, Position pos) : cmd{cmd}, piece{piece}, pos{pos} {};
    SetupInstruction(SetupCmds cmd, Position pos) : cmd{cmd}, pos{pos} {}
    SetupInstruction(SetupCmds cmd, Color color) : cmd{cmd}, color{color} {}
    SetupInstruction(SetupCmds cmd) : cmd{cmd} {}
};

#endif