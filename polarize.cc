#include "polarize.h"
using namespace std;

Polarize::Polarize(char playerId) : Ability{playerId} {}

// changes a targeted data to a virus of the same strength, or vice versa

void Polarize::use(Cell *c) {
    
}

string Polarize::getName() const { return "Polarize"; }
