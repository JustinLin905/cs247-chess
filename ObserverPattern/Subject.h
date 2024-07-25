#ifndef SUBJECT_H
#define SUBJECT_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Observer.h"

class Subject {
  std::vector<std::unique_ptr<Observer>> observers;

 public:
  void attach(std::unique_ptr<Observer> o);
  void detach(std::unique_ptr<Observer> o);
  void notifyObservers();
  virtual char getState(int row, int col) const = 0;
  virtual ~Subject() = default;
};

#endif