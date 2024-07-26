#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "../Player/Player.h"

class HumanPlayer : public Player {
   public:
    HumanPlayer(Color color, Game& game);
    Move getMove() override;
};

#endif