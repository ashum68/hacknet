#ifndef ABILITY_H
#define ABILITY_H
#include "cell.h"
#include "player.h"
using namespace std;

class Ability {
    char playerId;
    bool isUsed = false;
    public:
        Ability(char playerId);
        bool getUsed() const;
        void setUsed();
        virtual bool use(Cell* c);
        virtual string getName() const = 0;
};

#endif