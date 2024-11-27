#include "firewall.h"
using namespace std;

Firewall::Firewall(int playerId) : Ability{playerId} {}

// a link being "revealed" as its strength and type being revealed.

bool Firewall::use(Cell *c) {
    if (playerId == 1) {
        if (c->isFirewallOn2()) return false;
        c->setFirewall2();
    } else {
        if (c->isFirewallOn1()) return false;
        c->setFirewall2();
    }
    return true;
}

string FireWall::getName() const { return "Firewall"; }
