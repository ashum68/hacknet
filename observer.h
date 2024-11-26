#ifndef _OBSERVER_H_
#define _OBSERVER_H_

#include "game.h"

class Observer {
    Game* game;
    public:
        virtual void notify() = 0;
        virtual ~Observer() = default;
};

#endif
