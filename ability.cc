#include "ability.h"

Ability::Ability(Player *player) : player{player} {}

bool Ability::getUsed() const { return isUsed; }

void Ability::setUsed() { isUsed = true; }
