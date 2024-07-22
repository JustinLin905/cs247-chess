#include "Subject.h"

#include "Observer.h"

void Subject::attach(std::unique_ptr<Observer> o) { observers.emplace_back(o); }

void Subject::detach(std::unique_ptr<Observer> o) {
  observers.erase(std::remove(observers.begin(), observers.end(), o),
                  observers.end());
}

void Subject::notifyObservers() {
  for (auto &o : observers) {
    o->notify();
  }
}