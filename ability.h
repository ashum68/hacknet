#ifndef ABILITY_H
#define ABILITY_H
#include "cell.h"
#include <string>

class Player;

class Ability {
    protected:
        Player *player;
        bool isUsed = false;
    public:
        Ability(Player *player);
        virtual ~Ability() = default;
        bool getUsed() const;
        void setUsed();
        virtual bool use(Cell* c) = 0;
        virtual std::string getName() const = 0;
};

#endif
