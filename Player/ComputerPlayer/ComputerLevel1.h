#ifndef COMPUTER_LEVEL1_H
#define COMPUTER_LEVEL1_H

#include <random>

#include "ComputerPlayer.h"

class ComputerLevel1 : public ComputerPlayer {
public:
    ComputerLevel1(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game);
    Move getMove() override;
};

#endif