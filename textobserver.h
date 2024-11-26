#include "observer.h"
#include "board.h"
#ifndef _TEXT_OBSERVER_H_
#define _TEXT_OBSERVER_H_

class TextObserver : public Observer {
    Game* game;
    public:
        TextObserver(Board* board) : board(board) {} // modify
        void notify() override;
};

#endif