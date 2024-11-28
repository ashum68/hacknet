#include "linkboost.h"
using namespace std;

RoadWorkAhead::RoadWorkAhead(Player *player) : Ability{player} {}

bool RoadWorkAhead::use(Cell *c) {
    
}

string RoadWorkAhead::getName() const { return "Road Work Ahead"; }