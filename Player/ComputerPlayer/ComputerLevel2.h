#ifndef COMPUTER_LEVEL2_H
#define COMPUTER_LEVEL2_H

#include "ComputerPlayer.h"

class ComputerLevel2 : public ComputerPlayer {
   public:
    ComputerLevel2(Color color, std::shared_ptr<ChessBoard> board);
    Move getMove() override;
};

#endif