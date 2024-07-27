#ifndef GAME_H
#define GAME_H

#include "../ChessBoard/ChessBoard.h"
#include "../Move/Move.h"
#include "../Player/Player.h"
#include "../PlayerType/PlayerType.h"

class Game {
    ChessBoard& _board;
    Player& _white;
    Player& _black;

   public:
    void initPlayers(PlayerType::Type white, PlayerType::Type black);
    bool makeTurn(Move move);
    void reverseMoves(int n);

    Player& getWhite() { return _white; }
    Player& getBlack() { return _black; }
};

#endif