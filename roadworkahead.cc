#include "roadworkahead.h"
#include "player.h"

RoadWorkAhead::RoadWorkAhead(Player *player) : Ability{player} {}

bool RoadWorkAhead::use(Cell *c) {
    if (!c) return false;
    
    // check if the cell has a link
    if (c->getLink() != nullptr) {
        return false;
    }
    
    c->setBlocked(true);
    return true;
}

string RoadWorkAhead::getName() const { return "Road Work Ahead"; }