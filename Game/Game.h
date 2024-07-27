#ifndef GAME_H
#define GAME_H

#include <memory>

#include "../ChessBoard/ChessBoard.h"
#include "../Move/Move.h"
#include "../ObserverPattern/GraphicsObserver.h"
#include "../ObserverPattern/TextObserver.h"
#include "../Player/Player.h"
#include "../PlayerType/PlayerType.h"

class Game {
    std::shared_ptr<ChessBoard> _chess_board;
    std::unique_ptr<Player> _white;
    std::unique_ptr<Player> _black;

    GraphicsObserver graphics_observer;
    TextObserver text_observer;

   public:
    Game(PlayerType::Type white, PlayerType::Type black);
    void initDefaultGame();
    bool makeTurn(Move move);
    void reverseMoves(int n);

    void renderBoard() const;

    Player& getWhite() const;
    Player& getBlack() const;
};

#endif