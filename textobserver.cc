#include "textobserver.h"
#include <iostream>

TextObserver::TextObserver(Game* game) : game{game} {}

void TextObserver::notify() {
    displayBoard();
}
    
char TextObserver::getLinkDisplay(const Link* link) const {
    if (!link) return '.';
    return link->getId();
}

void TextObserver::displayPlayerInfo(const unique_ptr<Player> player, bool isCurrentPlayer) const {
    std::cout << "Player " << player->getId() + 1 << ":" << std::endl;
    std::cout << "Downloaded: " << player->getDownloadedData() << "D, " << player->getDownloadedViruses() << "V" << std::endl;
    int abilities = 0;
    for (const auto &a: player->getAbilities()) {
        if (!a->getUsed()) {
            abilities++;
        }
    }
    
    std::cout << "Abilities: " << abilities << " ";
    
    for (const auto& link : player->getLinks()) {
        if (!link->getDownloaded()) {
            char id = link->getId();
            if (isCurrentPlayer || link->isRevealed()) {
                std::cout << (link->getIsVirus() ? "V" : "D") << link->getStrength();
            } else {
                std::cout << "?";
            }
            
            // Add space or newline
            if (std::tolower(id) == 'd' || std::tolower(id) == 'h') {
                std::cout << std::endl;
            } else {
                std::cout << " ";
            }
        }
    }
}

void TextObserver::displayBoard() const {
    int currentPlayer = game->getCurrPlayer();
    
    displayPlayerInfo(game->getPlayer(0), currentPlayer == 0);
    
    std::cout << "========" << std::endl;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Cell* cell = game->getBoard()->getCell(i, j);
            if ((i == 0 && (j == 3 || j == 4)) || 
                (i == 7 && (j == 3 || j == 4))) {
                std::cout << 'S';
            } else if (cell->getLink()) {
                std::cout << getLinkDisplay(cell->getLink());
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "========" << std::endl;
    
    displayPlayerInfo(game->getPlayer(1), currentPlayer == 1);
}