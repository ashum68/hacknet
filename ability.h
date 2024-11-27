#ifndef ABILITY_H
#define ABILITY_H
#include "cell.h"
#include "player.h"
using namespace std;

class Ability {
    protected:
        int playerId;
        bool isUsed = false;
    public:
        Ability(int playerId);
        bool getUsed() const;
        void setUsed();
        virtual bool use(Cell* c) = 0;
        virtual string getName() const = 0;
};

#endif