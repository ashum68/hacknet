#include "ability.h"

Ability::Ability(char playerId) : playerId{playerId} {}

bool Ability::getUsed() const { return isUsed; }

void Ability::setUsed() { isUsed = true; }
