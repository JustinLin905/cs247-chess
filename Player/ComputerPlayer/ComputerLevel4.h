#ifndef COMPUTER_LEVEL4_H
#define COMPUTER_LEVEL4_H

#include "ComputerPlayer.h"

class ComputerLevel4 : public ComputerPlayer {
   public:
    ComputerLevel4(Color color, std::weak_ptr<ChessBoard> board, std::weak_ptr<Game> game);
    Move getMove() override;
};

#endif