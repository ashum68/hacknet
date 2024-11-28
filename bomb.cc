#include "bomb.h"
using namespace std;

Bomb::Bomb(Player *player, Board* board) : Ability{player}, board{board} {}

bool Bomb::use(Cell *c) {
    int row = c->getRow();
    int col = c->getCol();
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int new_row = row + dr; 
            int new_col = col + dc; 

            if (new_row >= 0 && new_col >= 0 && new_row < board->getSize() && new_col < board->getSize()) {
                Link *link = board->getCell(new_row, new_col)->getLink();
                if (link) {
                    link->setStrength(link->getStrength() - 1);
                } 
            }
        }
    }
    return true;
}

string Bomb::getName() const { return "Bomb"; }