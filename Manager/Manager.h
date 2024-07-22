#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include "PlayerType.h"

class Manager {
    Manager();

   public:
    Manager(Manager const&) = delete;
    Manager& operator=(Manager const&) = delete;

    static std::shared_ptr<Manager> instance() {
        static std::shared_ptr<Manager> m{new Manager};
        return m;
    }

    static void setupGame();
    static void startGame(PlayerType::Type white, PlayerType::Type black);
    static void closeGame();
};

#endif