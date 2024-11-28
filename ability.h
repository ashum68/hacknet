#ifndef ABILITY_H
#define ABILITY_H
#include "cell.h"
#include "player.h"
using namespace std;

class Ability {
    protected:
        Player *player;
        bool isUsed = false;
    public:
        Ability(Player *player);
        bool getUsed() const;
        void setUsed();
        virtual bool use(Cell* c) = 0;
        virtual string getName() const = 0;
};

#endif