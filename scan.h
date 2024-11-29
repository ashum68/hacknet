#ifndef SCAN_H
#define SCAN_H
#include "ability.h"
using namespace std;

class Scan : public Ability {
    public:
        Scan(Player *player);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
