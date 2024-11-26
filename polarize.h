#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"
using namespace std;

class Polarize : public Ability {
    public:
        Polarize(char playerId);
        void use(Cell *c) override;
        string getName() const override;
};

#endif
