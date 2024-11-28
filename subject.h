#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
protected:
    std::vector<Observer*> observers;

public:
    virtual void attach(Observer* o);
    virtual void detach(Observer* o);
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

#endif
