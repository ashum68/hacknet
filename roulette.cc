#include "roulette.h"
using namespace std;

Roulette::Roulette(Player *player) : Ability{player} {}

bool Roulette::use(Cell *c) {
    return;
}

string Roulette::getName() const { return "Roulette"; }