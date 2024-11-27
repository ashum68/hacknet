#ifndef ROADWORKAHEAD_H
#define ROADWORKAHEAD_H
#include "ability.h"
using namespace std;

class RoadWorkAhead : public Ability {
    public:
        RoadWorkAhead(int playerId);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif