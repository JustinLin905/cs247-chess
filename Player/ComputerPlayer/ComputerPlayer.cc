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

bool ComputerPlayer::isCaptureMove(Move move) {
    
    if (move.type == MoveType::ENPASSANT) return true; // all empassant moves are capture moves
    else {
        // if the final position of the move lands on an non-empty square, it's a capture move
        if (_chess_board.lock()->getSquare(move.final_pos).getPiece() != nullptr) return true;
    }

    return false;
}

PromotionType::Type ComputerPlayer::getPromotionPiece() { return PromotionType::Type::QUEEN; }
