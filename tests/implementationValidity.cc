#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>

#include "../ChessBoard/ChessBoard.h"
#include "../Game/Game.h"
#include "../Manager/Manager.h"
#include "../Move/Move.h"
#include "../PlayerType/PlayerType.h"
#include "../Position/Position.h"
#include "../enums.h"

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();  // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

TEST(ImplementationValidity, GameImplemenation) {
    const std::string TEST_FILE_PREFIX = "./tests/testFiles/test";
    const std::string TEST_FILE_EXTENSION = ".txt";
    const std::string TEST_FILE_BOARD_SUFFIX = "board";

    for (int i = 44; i <= 132; i++) {
        std::string test_file = TEST_FILE_PREFIX + std::to_string(i) + TEST_FILE_EXTENSION;
        std::ifstream file{test_file};

        if (!file.is_open()) {
            std::cerr << "Could not open file: " << test_file << std::endl;
            return;
        }

        Manager::startTestGame();

        std::cout << "NEW GAME STARTED" << std::endl;

        std::string cmd, from, to;

        // std::cout.setstate(std::ios_base::failbit);  // to prevent outpout from game

        while (file >> cmd >> from >> to) {
            // std::cout << cmd << " " << from << " " << to << std::endl;

            char og_col = from[0];
            int og_row = (int)from[1] - '0';
            char new_col = to[0];
            int new_row = (int)to[1] - '0';

            Move move(Position{8 - og_row, (int)og_col - 97}, Position{8 - new_row, (int)new_col - 97});

            try {
                Manager::playTurnInTestGame(move);
            } catch (std::exception e) {
                std::cout.clear();
                std::cout << "FILE :" << test_file << std::endl;
                std::cout << move << std::endl;
            }
        }

        std::cout.clear();

        // bool in_check = Manager::_turn % 2 == 0 ? Manager::getCurrGame()->getWhite().inCheck() : Manager::getCurrGame()->getBlack().inCheck();
        // bool any_valid_moves = Manager::getCurrGame()->anyValidMoves(Manager::_turn % 2 == 0 ? Color::WHITE : Color::BLACK);

        // EXPECT_TRUE(!any_valid_moves && in_check);

        file.close();

        std::string board_test_file = TEST_FILE_PREFIX + std::to_string(i) + TEST_FILE_BOARD_SUFFIX + TEST_FILE_EXTENSION;
        std::ifstream board_file{board_test_file};

        if (!board_file.is_open()) {
            std::cerr << "Could not open file: " << board_test_file << std::endl;
            return;
        }

        std::string board_line;
        std::vector<std::string> board_lines;
        ChessBoard& cb = Manager::getCurrGame()->getChessBoard();

        Manager::getCurrGame()->renderBoard();

        while (std::getline(board_file, board_line)) {
            board_line = ReplaceAll(board_line, " ", "");
            board_line = ReplaceAll(board_line, ".", "-");
            board_lines.push_back(board_line);
        }

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                auto p = cb.getSquare(Position{i, j}).getPiece();
                char c = p != nullptr ? p->getPieceChar() : '-';
                if (c != board_lines.at(i).at(j)) throw std::runtime_error("Board mismatch");
                EXPECT_EQ(c, board_lines.at(i).at(j));
            }
        }

        board_file.close();

        std::cout << "CLOSING GAME FOR " << test_file << std::endl;
        Manager::closeGame();
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    return 0;
}