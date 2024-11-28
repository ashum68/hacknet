#include "scan.h"
using namespace std;

Scan::Scan(Player *player) : Ability{player} {}

bool Scan::use(Cell *c) {
    Link *link = c->getLink();
    if (!link || link->isRevealed()) return false;
    link->setRevealed();
    return true;
}

string Scan::getName() const { return "Scan"; }
