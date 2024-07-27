#ifndef COMPUTER_LEVEL4_H
#define COMPUTER_LEVEL4_H

#include "ComputerPlayer.h"

class ComputerLevel4 : public ComputerPlayer {
   public:
    ComputerLevel4(Color color, std::shared_ptr<ChessBoard> board);
    Move getMove() override;
};

#endif