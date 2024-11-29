#include "polarize.h"
#include "player.h"
#include "link.h"

Polarize::Polarize(Player *player) : Ability{player} {}

bool Polarize::use(Cell *c) {
    if (!c || !c->getLink()) return false;
    
    Link *link = c->getLink();
    link->setVirus();
    return true;
}

string Polarize::getName() const { return "Polarize"; }
