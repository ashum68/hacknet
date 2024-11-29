#include "firewall.h"
#include "player.h"
#include <iostream>
using namespace std;

Firewall::Firewall(Player *player) : Ability{player} {}

bool Firewall::use(Cell *c) {
    if (player->getId() == 0) {
        if (c->isFirewallOn2()) return false;
        c->setFirewall2();

    } else {
        if (c->isFirewallOn1()) return false;
        c->setFirewall1();
    }
    return true;
}

string Firewall::getName() const { return "Firewall"; }
