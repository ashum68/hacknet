#ifndef FIREWALL_H
#define FIREWALL_H
#include "ability.h"
using namespace std;

class Firewall : public Ability {
    public:
        Firewall(Player *player);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
