#include "Subject.h"

#include <iostream>

#include "Observer.h"

void Subject::attach(Observer* o) {
    observers.emplace_back(o);
}

void Subject::detach(Observer* o) {
    observers.erase(remove(observers.begin(), observers.end(), o), observers.end());
}

void Subject::notifyObservers() {
    for (auto &o : observers) {
        o->notify();
    }
}