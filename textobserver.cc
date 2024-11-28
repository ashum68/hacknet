#include "textobserver.h"
#include <iostream>

void TextObserver::notify() {
    std::cout << "Player 1:" << endl;
    auto player1 = game->getPlayers()[0]
    std::cout << "Downloaded Data: " << player1->getDownloadedData() << "D, " << player1->getDownloadedViruses() << "V" << endl;
    int abilities = 0;


    for (auto a: player1->getAbilities()) {
        if (!a->getIsUsed()) {
            abilities++;
        }
    }


    std::cout << "Abilities: " << abilities << endl;
    auto links = player1->getLinks();


    for (auto link : links) {
        std::cout << link->getId() << ": " << link->isVirus() ? "V" : "D" << link->getStrength() << (std::tolower(link->getId()) == 'd' || std::tolower(link->getId()) == 'h' ) ? std::endl : " ";
    }

    std::cout << "========" << std::endl;
    
}