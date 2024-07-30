#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "../Player.h"
#include <random>

class ComputerPlayer : public Player {
    std::random_device seed;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen{seed()};

protected:
    std::weak_ptr<ChessBoard> _chess_board;

public:
    ComputerPlayer(Color color, std::weak_ptr<ChessBoard> chess_board) : Player{color}, _chess_board{chess_board} {};
    virtual Move getMove() override = 0;
    virtual ~ComputerPlayer() = default;
    Move getRandomMove(const std::unordered_set<Move>& moveSet);
};

#endif