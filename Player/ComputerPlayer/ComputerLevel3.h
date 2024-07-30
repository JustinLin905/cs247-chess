#ifndef COMPUTER_LEVEL3_H
#define COMPUTER_LEVEL3_H

#include "ComputerPlayer.h"

class ComputerLevel3 : public ComputerPlayer {
   public:
    ComputerLevel3(Color color, std::weak_ptr<ChessBoard> board);
    Move getMove() override;
};

#endif