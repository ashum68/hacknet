#include "linkboost.h"
using namespace std;

RoadWorkAhead::RoadWorkAhead(char playerId) : Ability{playerId} {}

bool RoadWorkAhead::use(Cell *c) {
    
}

string RoadWorkAhead::getName() const { return "Road Work Ahead"; }