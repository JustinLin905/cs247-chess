#include "Subject.h"

#include <iostream>

#include "Observer.h"

void Subject::attach(std::shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::detach(std::shared_ptr<Observer> o) {
    observers.erase(std::remove_if(observers.begin(), observers.end(), [&o](const std::shared_ptr<Observer> &obs) { return obs.get() == o.get(); }), observers.end());
}

void Subject::notifyObservers() {
    for (auto &o : observers) {
        o->notify();
    }
}