#include "ability.h"

Ability::Ability(int playerId) : playerId{playerId} {}

bool Ability::getUsed() const { return isUsed; }

void Ability::setUsed() { isUsed = true; }
