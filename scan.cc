#include "scan.h"
using namespace std;

// reveals the type and strength of any targeted link on the field. It does not reveal the player’s own links

Scan::Scan(Player *player) : Ability{player} {}

void Scan::use(Cell *c) {
    /* Impl */
}

string Scan::getName() const { return "Scan"; }
