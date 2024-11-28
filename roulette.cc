#include "roulette.h"
using namespace std;

Roulette::Roulette(Player *player) : Ability{player} {}

bool Roulette::use(Cell *c) {

    std::srand(std::time(0)); 
    int n1 = std::rand() % 3 + 1;
    int n2 = std::rand() % 3 + 1;
    if (n1 == n2) {
        player->incDownloadedData();
    } else {
        player->incDownloadedViruses();
    }
}

string Roulette::getName() const { return "Roulette"; }
