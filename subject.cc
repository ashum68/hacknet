#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach( Observer* o ) {
    observers.emplace_back(o);
}

void Subject::detach( Observer* o ) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            return;
        } 
    }
}

void Subject::notifyObservers() {
    /*** FILL IN ***/
    for (auto o : observers) {
        o->notify();
    }
}