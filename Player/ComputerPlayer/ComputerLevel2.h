#ifndef COMPUTER_LEVEL2_H
#define COMPUTER_LEVEL2_H

#include "ComputerPlayer.h"
#include <random>

class ComputerLevel2 : public ComputerPlayer {
    std::random_device seed;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen{seed()};

public:
    ComputerLevel2(Color color, std::weak_ptr<ChessBoard> board);
    Move getMove() override;
};

#endif