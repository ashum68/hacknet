#include "linkboost.h"
using namespace std;

LinkBoost::LinkBoost(int playerId) : Ability{playerId} {}

bool LinkBoost::use(Cell *c) {
    Link *link = c->getLink();
    if (!link) return false;
    link->addBoosted();
    return true;
}

string LinkBoost::getName() const { return "Link Boost"; }
