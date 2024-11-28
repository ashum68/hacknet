#include "bomb.h"
using namespace std;

Bomb::Bomb(Player *player) : Ability{player} {}

bool Bomb::use(Cell *c) {
   
}

string Bomb::getName() const { return "Bomb"; }