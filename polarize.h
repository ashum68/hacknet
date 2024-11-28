#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"
using namespace std;

class Polarize : public Ability {
    public:
        Polarize(Player *player);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
