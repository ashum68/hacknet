#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include <vector>
#include "ability.h"
using namespace std;

class Download : public Ability {
    public:
        void use(Cell *c) override;
        string getName() const override;
};

#endif
