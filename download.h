#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "ability.h"
using namespace std;

class Download : public Ability {
    public:
        Download(char playerId); // int?
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
