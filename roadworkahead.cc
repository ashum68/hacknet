#include "roadworkahead.h"
#include "player.h"

RoadWorkAhead::RoadWorkAhead(Player *player) : Ability{player} {}

bool RoadWorkAhead::use(Cell *c) {
    if (!c) return false;
    
    // Check if the cell is already occupied by a link
    if (c->getLink() != nullptr) {
        // Cannot block an occupied cell
        return false;
    }

    // Block the cell since it's not occupied
    c->setBlocked(true);
    return true;
}

string RoadWorkAhead::getName() const { return "Road Work Ahead"; }