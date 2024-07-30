// #include <gtest/gtest.h>

// #include <fstream>
// #include <iostream>
// #include <string>

// #include "../Game/Game.h"
// #include "../Move/Move.h"
// #include "../PlayerType/PlayerType.h"
// #include "../Position/Position.h"
// #include "../enums.h"

// TEST(ImplementationValidity, GameImplemenation) {
//     const std::string TEST_FILE_PREFIX = "test";
//     const std::string TEST_FILE_EXTENSION = ".txt";

//     for (int i = 0; i < 1; i++) {
//         std::string test_file = TEST_FILE_PREFIX + std::to_string(i) + TEST_FILE_EXTENSION;
//         std::ifstream file(test_file);

//         Game game;
//         game.setupPlayers(PlayerType::Type::HUMAN, PlayerType::Type::HUMAN);
//         game.initDefaultGame();

//         std::string move, from, to;

//         int turn_count = 0;

//         while (file >> move >> from >> to) {
//             char og_col = from[0];
//             int og_row = (int)from[1] - '0';
//             char new_col = to[0];
//             int new_row = (int)to[1] - '0';

//             Move move(Position{8 - og_row, (int)og_col - 97}, Position{8 - new_row, (int)new_col - 97});
//             game.makeTurn(move, turn_count % 2 == 0 ? Color::WHITE : Color::BLACK, false);
//         }

//         bool in_check = turn_count % 2 == 0 ? game.getWhite().inCheck() : game.getBlack().inCheck();
//         bool any_valid_moves = game.anyValidMoves(turn_count % 2 == 0 ? Color::WHITE : Color::BLACK);
//         EXPECT_TRUE(!any_valid_moves && in_check);
//     }
// }

// // int main(int argc, char **argv) {
// //     ::testing::InitGoogleTest(&argc, argv);
// //     return RUN_ALL_TESTS();
// // }