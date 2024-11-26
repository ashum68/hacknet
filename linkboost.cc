#include "linkboost.h"
using namespace std;

bool LinkBoost::use(Cell *c) {
    Link *link = c->getLink();
    if (!link || link->isBoosted()) return false;
    link->setBoosted();
    return true;
}

string LinkBoost::getName() const { return "Link Boost"; }
