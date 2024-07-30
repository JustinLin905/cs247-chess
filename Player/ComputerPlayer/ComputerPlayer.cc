#include "ComputerPlayer.h"
#include "../../CommandInterpreter/PromotionCmds.h"
#include "../../Move/Move.h"
#include <random>

Move ComputerPlayer::getRandomMove(const std::unordered_set<Move>& moveSet) {

    std::uniform_int_distribution<> dist{0, moveSet.size() - 1};
    int move_index = dist(gen);

    int counter = 0;

    for (auto it = moveSet.begin(); it != moveSet.end(); ++it, counter++) {
        if (counter == move_index) return *it;
    }
}

PromotionType::Type ComputerPlayer::getPromotionPiece() { return PromotionType::Type::QUEEN; }
