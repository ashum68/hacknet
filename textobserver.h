#include "observer.h"
#include "board.h"
#ifndef _TEXT_OBSERVER_H_
#define _TEXT_OBSERVER_H_

class TextObserver : public Observer {
    Board* board;

    public:
        TextObserver(Board* board) : board(board) {}
        void notify() override;
};

#endif