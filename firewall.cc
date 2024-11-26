#include "firewall.h"
using namespace std;

Firewall::Firewall(char playerId) : Ability{playerId} {}

bool Firewall::use(Cell *c) {
    Link *link = c->getLink();
    if (!link) return false;
    char playerId = link->getPlayerId();
    if (!playerId) return false;

}

string FireWall::getName() const { return "Firewall"; }
