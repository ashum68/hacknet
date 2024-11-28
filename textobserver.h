#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "board.h"
#include "player.h"
#include "game.h"
#include <memory>

class TextObserver : public Observer {
    Game* game;
    
    public:
        TextObserver(Game* game);
        void notify() override;
        char getLinkDisplay(const Link* link) const;
        void displayBoard() const;
        void displayPlayerInfo(const Player* player, bool showLinks) const;
};

#endif
