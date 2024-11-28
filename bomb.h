#ifndef BOMB_H
#define BOMB_H
#include "ability.h"
#include "board.h"
using namespace std;

class Bomb : public Ability {
    Board *board;
    public:
        Bomb(Player *player, Board *board);
        bool use(Cell *c) override;
        string getName() const override;
};

#endif
