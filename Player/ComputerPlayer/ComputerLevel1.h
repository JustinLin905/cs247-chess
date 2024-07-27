#ifndef COMPUTER_LEVEL1_H
#define COMPUTER_LEVEL1_H

#include <random>

#include "ComputerPlayer.h"

class ComputerLevel1 : public ComputerPlayer {
    std::random_device seed;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen{seed()};

   public:
    ComputerLevel1(Color color, std::shared_ptr<Game> game);
    Move getMove() override;
};

#endif