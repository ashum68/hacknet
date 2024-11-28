#ifndef BOMB_H
#define BOMB_H
#include "ability.h"
using namespace std;

class Bomb : public Ability {
    public:
        Bomb(Player *player);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
