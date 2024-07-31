#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "../Player.h"
#include "../../CommandInterpreter/PromotionCmds.h"
#include <random>

class ComputerPlayer : public Player {
    std::random_device seed;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen{seed()};

protected:
    std::weak_ptr<ChessBoard> _chess_board;
    Move getRandomMove(const std::unordered_set<Move>& moveSet);
    bool isCaptureMove(Move move);

public:
    ComputerPlayer(Color color, std::weak_ptr<ChessBoard> chess_board, std::weak_ptr<Game> game) : Player{color, game}, _chess_board{chess_board} {};
    virtual Move getMove() override = 0;
    virtual ~ComputerPlayer() = default;
    virtual PromotionType::Type getPromotionPiece();
};

#endif