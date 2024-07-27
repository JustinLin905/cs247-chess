#ifndef GAME_H
#define GAME_H

#include <memory>

#include "../ChessBoard/ChessBoard.h"
#include "../Move/Move.h"
#include "../Player/Player.h"
#include "../PlayerType/PlayerType.h"

class Game {
    ChessBoard _board;
    std::unique_ptr<Player> _white;
    std::unique_ptr<Player> _black;

   public:
    void initPlayers(PlayerType::Type white, PlayerType::Type black);
    bool makeTurn(Move move);
    void reverseMoves(int n);

    std::unique_ptr<Player> getWhite() const;
    std::unique_ptr<Player> getBlack() const;
};

#endif