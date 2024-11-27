#include "linkboost.h"
using namespace std;

LinkBoost::LinkBoost(int playerId) : Ability{playerId} {}

// link boosts can be stacked

bool LinkBoost::use(Cell *c) {
    Link *link = c->getLink();
    if (!link || link->isBoosted()) return false;
    link->setBoosted();
    return true;
}

string LinkBoost::getName() const { return "Link Boost"; }
