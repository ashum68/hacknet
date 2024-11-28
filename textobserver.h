#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "observer.h"
#include "board.h"
#include "player.h"
#include <memory>

class TextObserver : public Observer {
    Board* board;
    
    public:
        TextObserver(Board* board);
        void notify() override;
        char getLinkDisplay(const Link* link) const;
        void displayBoard() const;
        void displayPlayerInfo(const Player* player, bool showLinks) const;
};

#endif
