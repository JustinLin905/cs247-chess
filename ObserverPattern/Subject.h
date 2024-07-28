#ifndef SUBJECT_H
#define SUBJECT_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Observer.h"

class Subject {
   public:
    std::vector<Observer*> observers;
    void attach(Observer* o);
    void detach(Observer* o);
    void notifyObservers();
    virtual char getState(int row, int col) const = 0;
    virtual ~Subject() = default;
};

#endif