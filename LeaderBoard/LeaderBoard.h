#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <iostream>

class LeaderBoard {
 private:
  float _white_score;
  float _black_score;
  void addScore(float white_score, float black_score);

 public:
  LeaderBoard() = default;
  ~LeaderBoard() = default;
  void winWhite();
  void winBlack();
  void draw();
  void printScores();
  void resetScores();
};

#endif