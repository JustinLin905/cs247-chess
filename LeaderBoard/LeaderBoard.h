#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <utility>

class LeaderBoard {
 private:
  int _white_score;
  int _black_score;

 public:
  LeaderBoard() = default;
  ~LeaderBoard() = default;
  void addScore(int white_score, int black_score);
  std::pair<int, int> getScores();
  void resetScores();
};

#endif