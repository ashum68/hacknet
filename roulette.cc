#include "roulette.h"
#include "player.h"
#include <random>
using namespace std;

Roulette::Roulette(Player *player) : Ability{player} {}

bool Roulette::use(Cell *c) {
    // Use random_device and mt19937 for better randomization
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 3);
    
    int result = dis(gen);
    
    if (result <= 2) {  // 2/3 chance of success
        player->incDownloadedData();
    } else {  // 1/3 chance of failure
        player->incDownloadedViruses();
    }
    return true;
}

string Roulette::getName() const { return "Roulette"; }