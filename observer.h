#ifndef OBSERVER_H
#define OBSERVER_H

class Subject;
class Game;

class Observer {
    [[maybe_unused]] Game* game;
public:
    virtual void notify() = 0;
    virtual ~Observer() = default;
};

#endif
