#ifndef ROULETTE_H
#define ROULETTE_H
#include "ability.h"
using namespace std;

class Scan : public Ability {
    public:
        Scan(char playerId);
        void use(Cell *c) override;
        string getName() const override;
};

#endif
