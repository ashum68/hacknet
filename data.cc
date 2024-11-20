#include "data.h"

Data::Data(char id, int strength, Player* owner) : Link{id, strength, owner} {}

bool Data::isVirus() const {
    return false;
}
