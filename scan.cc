#include "scan.h"
#include "player.h"

Scan::Scan(Player *player) : Ability{player} {}

bool Scan::use(Cell *c) {
    if (!c || !c->getLink()) return false;
    
    Link* targetLink = c->getLink();
    targetLink->reveal();
    
    return true;
}

string Scan::getName() const { return "Scan"; }
