#ifndef GAME_H
#define GAME_H

#include "../Move/Move.h"
#include "../PlayerType/PlayerType.h"

class Game {
   public:
    void initPlayers(PlayerType::Type white, PlayerType::Type black);
    bool makeTurn(Move move);
    void reverseMoves(int n);
};

#endif