#ifndef COMPUTER_LEVEL1_H
#define COMPUTER_LEVEL1_H

#include "ComputerPlayer.h"

class ComputerLevel1 : public ComputerPlayer {
   public:
    ComputerLevel1(Color color, std::shared_ptr<ChessBoard> board);
    Move getMove() override;
};

#endif