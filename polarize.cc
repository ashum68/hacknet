#include "polarize.h"
using namespace std;

Polarize::Polarize(int playerId) : Ability{playerId} {}

// changes a targeted data to a virus of the same strength, or vice versa

bool Polarize::use(Cell *c) {
    Link *link = c->getLink();
    link->setVirus();
    return true;
}

string Polarize::getName() const { return "Polarize"; }
