#ifndef LINKBOOST_H
#define LINKBOOST_H
#include "ability.h"
using namespace std;

class LinkBoost : public Ability {
    public:
        LinkBoost(char playerId);
        void use(Cell *c) override;
        string getName() const override;
};

#endif
