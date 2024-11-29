#include "roulette.h"
#include "player.h"
#include <random>
using namespace std;

Roulette::Roulette(Player *player) : Ability{player} {}

bool Roulette::use(Cell *c) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);
    
    int result = dis(gen);
    
    if (result == 1) {
        player->incDownloadedData();
    } else {
        player->incDownloadedViruses();
    }
    return true;
}

string Roulette::getName() const { return "Roulette"; }
