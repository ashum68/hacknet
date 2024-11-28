#include "observer.h"
#include "game.h"
#ifndef _TEXT_OBSERVER_H_
#define _TEXT_OBSERVER_H_

class TextObserver : public Observer {
    Game* game;
    public:
        TextObserver(Game* game) : game(game) {}
        void notify() override;
        char getLinkDisplay(const Link* link) const;
        void displayPlayerInfo(const unique_ptr<Player> player, bool isCurrentPlayer) const;
        void displayBoard() const;
};

#endif