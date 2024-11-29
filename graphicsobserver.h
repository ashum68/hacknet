#ifndef _GRAPHICS_OBSERVER_H
#define _GRAPHICS_OBSERVER_H

#include "observer.h"
#include "board.h"
#include "window.h"
#include "game.h"

class GraphicsObserver : public Observer {
    const int LINE_HEIGHT = 30;
    const int LINK_SPACING = 60;
    const int cellSize = 65;
    const int boardWidth = 8 * cellSize;
    const int boardHeight = 8 * cellSize;
    const int borderSize = 30;
    const int startX = 50;
    const int startY = 50;
    const int pieceSize = cellSize * 2/3;
    const int pieceOffset = (cellSize - pieceSize) / 2;
    const int borderWidth = 1;
    
    Game* game;
    Xwindow w;
    void renderCell(int r, int c, int cellSize, int boardOffset);
    void renderPlayerInfo(const Player* player, bool showLinks, int x, int y);

    public:
        GraphicsObserver(Game* game);
        ~GraphicsObserver() override = default;
        void notify() override;
        Xwindow& getWindow() { return w; }
};

#endif
