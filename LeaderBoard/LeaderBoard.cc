#include "LeaderBoard.h"

void LeaderBoard::addScore(float white_score, float black_score) {
    _white_score += white_score;
    _black_score += black_score;
}

void LeaderBoard::printScores(bool final) {
    std::cout << std::endl
              << "====================" << std::endl;

    if (final) {
        std::cout << "Final Scores:" << std::endl;
    } else {
        std::cout << "Current Scores:" << std::endl;
    }

    std::cout << "White: " << _white_score << std::endl;
    std::cout << "Black: " << _black_score << std::endl;

    std::cout << "====================" << std::endl;
}

void LeaderBoard::resetScores() {
    _white_score = 0;
    _black_score = 0;
}

void LeaderBoard::winWhite() { addScore(1, 0); }

void LeaderBoard::winBlack() { addScore(0, 1); }

void LeaderBoard::draw() { addScore(0.5, 0.5); }