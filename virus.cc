#include "virus.h"

Virus::Virus(char id, int strength, Player* owner) : Link{id, strength, owner} {}

bool Virus::isVirus() const {
    return true;
}
