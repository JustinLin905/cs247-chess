#include "Subject.h"

#include "Observer.h"

void Subject::attach(std::unique_ptr<Observer> o) {
  observers.emplace_back(std::move(o));
}

void Subject::detach(std::unique_ptr<Observer> o) {
  observers.erase(std::remove_if(observers.begin(), observers.end(),
                                 [&o](const std::unique_ptr<Observer> &obs) {
                                   return obs.get() == o.get();
                                 }),
                  observers.end());
}

void Subject::notifyObservers() {
  for (auto &o : observers) {
    o->notify();
  }
}