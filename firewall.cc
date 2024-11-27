#include "firewall.h"
using namespace std;

Firewall::Firewall(char playerId) : Ability{playerId} {}

// a link being "revealed" as its strength and type being revealed.

bool Firewall::use(Cell *c) {
    

}

string FireWall::getName() const { return "Firewall"; }
