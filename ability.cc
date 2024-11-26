#include "ability.h"

Ability::Ability(char playerId) : playerId{playerId} {}

bool Ability::getUsed() { return isUsed; }
