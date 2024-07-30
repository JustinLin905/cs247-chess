#ifndef COMPUTER_LEVEL2_H
#define COMPUTER_LEVEL2_H

#include "ComputerPlayer.h"
#include <random>

class ComputerLevel2 : public ComputerPlayer {
public:
    ComputerLevel2(Color color, std::weak_ptr<ChessBoard> board);
    Move getMove() override;
};

#endif