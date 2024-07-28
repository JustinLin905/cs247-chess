#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "../Player.h"

class ComputerPlayer : public Player {
   public:
    ComputerPlayer(Color color) : Player{color} {};
    virtual Move getMove() override = 0;
};

#endif