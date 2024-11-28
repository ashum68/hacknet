#include "roadworkahead.h"
using namespace std;

RoadWorkAhead::RoadWorkAhead(Player *player) : Ability{player} {}

bool RoadWorkAhead::use(Cell *c) {
    c->setBlocked();
    return true;
}

string RoadWorkAhead::getName() const { return "Road Work Ahead"; }