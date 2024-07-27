#include "ComputerLevel1.h"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <random>

#include "../../Move/Move.h"

Move ComputerLevel1::getMove() {
    while (true) {
        std::uniform_int_distribution<> dist{0, _alive_pieces.size() - 1};  // set min and max
        int piece_index = dist(gen);                                        // generate number
        auto valid_moves = _alive_pieces[piece_index]->getValidMoves();
        if (valid_moves.empty()) continue;

        std::uniform_int_distribution<> dist2{0, valid_moves.size() - 1};
        int move_index = dist(gen);

        int counter = 0;

        for (std::unordered_set<Move>::iterator it = valid_moves.begin(); it != valid_moves.end(); ++it, counter++) {
            if (counter == move_index) return *it;
        }
    }
}