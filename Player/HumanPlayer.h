#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "../Player/Player.h"

class HumanPlayer : public Player {
   public:
    HumanPlayer(Color color, std::weak_ptr<Game> game);
    Move getMove() override;
};

#endif