#include "justsayno.h"
using namespace std;

JustSayNo::JustSayNo(char playerId) : Ability{playerId} {}

bool JustSayNo::use(Cell *c) {
   
}

string JustSayNo::getName() const { return "Just Say No"; }