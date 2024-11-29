#include "bomb.h"
#include <iostream>
using namespace std;

Bomb::Bomb(Player *player, Board* board) : Ability{player}, board{board} {}

bool Bomb::use(Cell *c) {
    int row = c->getRow();
    int col = c->getCol();
    for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
            int new_row = row + dr; 
            int new_col = col + dc; 

            if (new_row >= 0 && new_col >= 0 && new_row < 8 && new_col < 8) {
                Cell *cell = board->getCell(new_row, new_col);
                Link *link = cell->getLink();
                if (link) {
                    link->decStrength();
                } 
            }
        }
    }
    return true;
}

string Bomb::getName() const { return "Bomb"; }
