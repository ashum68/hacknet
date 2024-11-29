#ifndef _GRAPHICS_OBSERVER_H
#define _GRAPHICS_OBSERVER_H

#include "observer.h"
#include "board.h"
#include "window.h"
#include "game.h"

class GraphicsObserver : public Observer {
    Game* game;
    Xwindow w;
    void renderCell(int r, int c, int cellSize, int boardOffset);
    void renderPlayerInfo(const Player* player, bool showLinks, int x, int y);
    void renderAbilitiesDisplay();

    public:
        GraphicsObserver(Game* game);
        ~GraphicsObserver() override = default;
        void notify() override;
        Xwindow& getWindow() { return w; }
};

#endif
