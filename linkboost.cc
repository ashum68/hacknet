#include "linkboost.h"
#include "link.h"

LinkBoost::LinkBoost(Player *player) : Ability{player} {}

bool LinkBoost::use(Cell *c) {
    if (!c || !c->getLink()) return false;
    
    Link *link = c->getLink();
    link->addBoosted();
    
    return true;
}

string LinkBoost::getName() const { return "Link Boost"; }
