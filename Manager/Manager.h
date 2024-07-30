#ifndef MANAGER_H
#define MANAGER_H

#include <memory>

// #include "../Game/Game.h"
#include "../LeaderBoard/LeaderBoard.h"
#include "../Move/Move.h"
#include "../PlayerType/PlayerType.h"
#include "../enums.h"

class Game;

class Manager {
    static std::shared_ptr<Game> _CurrGame;
    static std::unique_ptr<LeaderBoard> _leaderBoard;

    Manager();

   public:
    static int _turn;

    Manager(Manager const&) = delete;
    Manager& operator=(Manager const&) = delete;

    static std::shared_ptr<Manager> instance() {
        static std::shared_ptr<Manager> m{new Manager};
        return m;
    }

    static std::shared_ptr<Game> getCurrGame() { return _CurrGame; }
    static void setupGame();
    static void startGame(PlayerType::Type white, PlayerType::Type black);
    static void startTestGame();
    static void playTurnInTestGame(Move move);
    static void closeGame();
    static void setTurn(Color color);
    static LeaderBoard& getLeaderBoard();
};

#endif