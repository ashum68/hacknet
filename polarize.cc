#include "polarize.h"
using namespace std;

Polarize::Polarize(Player *player) : Ability{player} {}

bool Polarize::use(Cell *c) {
    Link *link = c->getLink();
    if (!link) return false;
    link->setVirus();
    return true;
}

string Polarize::getName() const { return "Polarize"; }
