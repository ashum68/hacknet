#ifndef JUSTSAYNO_H
#define JUSTSAYNO_H
#include "ability.h"
using namespace std;

class JustSayNo : public Ability {
    public:
        JustSayNo(char playerId);
        void use(Cell *c) override;
        string getName() const override;
};

#endif