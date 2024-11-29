#include "subject.h"
#include "observer.h"
#include <memory>
#include <vector>

void Subject::attach(std::unique_ptr<Observer> o ) {
    observers.push_back(std::move(o));
}

void Subject::detach(std::unique_ptr<Observer> o) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            return;
        } 
    }
}

void Subject::notifyObservers() {
    for (const auto& o : observers) {
        o->notify();
    }
}
