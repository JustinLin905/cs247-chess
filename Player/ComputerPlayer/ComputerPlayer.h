#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "../Player.h"

class ComputerPlayer : public Player {
   public:
    ComputerPlayer(Color color, std::shared_ptr<Game> game) : Player{color, game} {};
    virtual Move getMove() override = 0;
};

#endif