#include "Subject.h"

#include <iostream>

#include "Observer.h"

void Subject::attach(std::unique_ptr<Observer> o) {
    observers.emplace_back(std::move(o));
    std::cout << observers.size() << std::endl;
}

void Subject::detach(std::unique_ptr<Observer> o) {
    observers.erase(std::remove_if(observers.begin(), observers.end(),
                                   [&o](const std::unique_ptr<Observer> &obs) {
                                       return obs.get() == o.get();
                                   }),
                    observers.end());
}

void Subject::notifyObservers() {
    std::cout << observers.size() << std::endl;
    for (auto &o : observers) {
        o->notify();
    }
}