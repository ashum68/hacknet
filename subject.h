#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "observer.h"

class Subject {
protected:
    std::vector<std::unique_ptr<Observer>> observers;

public:
    virtual void attach(std::unique_ptr<Observer> o);
    virtual void detach(std::unique_ptr<Observer> o);
    virtual void notifyObservers() = 0;
    virtual ~Subject() = default;
};

#endif
