#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "../Player.h"

class ComputerPlayer : public Player {
protected:
    std::weak_ptr<ChessBoard> _chess_board;

public:
    ComputerPlayer(Color color, std::weak_ptr<ChessBoard> chess_board) : Player{color}, _chess_board{chess_board} {};
    virtual Move getMove() override = 0;
};

#endif