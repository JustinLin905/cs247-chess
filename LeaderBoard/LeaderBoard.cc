#include "LeaderBoard.h"

void LeaderBoard::addScore(int white_score, int black_score) {
  _white_score += white_score;
  _black_score += black_score;
}

std::pair<int, int> LeaderBoard::getScores() {
  return std::make_pair(_white_score, _black_score);
}

void LeaderBoard::resetScores() {
  _white_score = 0;
  _black_score = 0;
}