#ifndef _GRAPHICS_OBSERVER_H
#define _GRAPHICS_OBSERVER_H

#include "observer.h"
#include "board.h"
#include "window.h"

class GraphicsObserver : public Observer {
    Game* game;
    Xwindow w;

    public:
        GraphicsObserver(Board* board) : board(board) {}; // modify
        ~GraphicsObserver() override;
        void notify() override;
};

#endif
