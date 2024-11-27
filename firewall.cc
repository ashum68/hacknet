#include "firewall.h"
using namespace std;

Firewall::Firewall(char playerId) : Ability{playerId} {}

// a link being "revealed" as its strength and type being revealed.

bool Firewall::use(Cell *c) {
    Link *link = c->getLink();
    if (!link) return false;
    char playerId = link->getPlayerId();
    if (!playerId) return false;

}

string FireWall::getName() const { return "Firewall"; }
