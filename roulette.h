#ifndef ROULETTE_H
#define ROULETTE_H
#include "ability.h"
using namespace std;

class Roulette : public Ability {
    public:
        Roulette(Player *player);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
