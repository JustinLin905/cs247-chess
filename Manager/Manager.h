#ifndef MANAGER_H
#define MANAGER_H

#include "PlayerType.h"

class Manager {
   public:
    void setupGame();
    void startGame(PlayerType::Type White, PlayerType::Type Black);
    void closeGame();
};

#endif