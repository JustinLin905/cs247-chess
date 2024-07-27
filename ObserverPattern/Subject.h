#ifndef SUBJECT_H
#define SUBJECT_H

#include <algorithm>
#include <memory>
#include <vector>

#include "Observer.h"

class Subject {
   public:
    std::vector<std::shared_ptr<Observer>> observers;
    void attach(std::shared_ptr<Observer> o);
    void detach(std::shared_ptr<Observer> o);
    void notifyObservers();
    virtual char getState(int row, int col) const = 0;
    virtual ~Subject() = default;
};

#endif