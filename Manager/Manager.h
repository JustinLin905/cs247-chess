#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

#include "PlayerType.h"

// class Manager {
//    public:
//     static void setupGame();
//     static void startGame(PlayerType::Type White, PlayerType::Type Black);
//     static void closeGame();
// };

class Manager {
    Manager() {}

   public:
    Manager(Manager const&) = delete;
    Manager& operator=(Manager const&) = delete;

    static std::shared_ptr<Manager> instance() {
        static std::shared_ptr<Manager> s{new Manager};
        return s;
    }
};

#endif