#include "textobserver.h"
#include <iostream>

TextObserver::TextObserver(Board* board) : board{board} {}

void TextObserver::notify() {
    displayBoard();
}

void TextObserver::displayPlayerInfo(const Player* player, bool showLinks) const {
    std::cout << std::endl << "Player " << player->getId() + 1 << ":" << std::endl;
    std::cout << "Downloaded: " << player->getDownloadedData() << "D, " 
              << player->getDownloadedViruses() << "V" << std::endl;
    
    int availableAbilities = 0;
    for (const auto& ability : player->getAbilities()) {
        if (!ability->getUsed()) availableAbilities++;
    }
    std::cout << "Abilities: " << availableAbilities << std::endl;
    
    // Player 1 (id=0) always uses lowercase, Player 2 (id=1) always uses uppercase
    if (player->getId() == 0) {  // Player 1
        for (char c = 'a'; c <= 'h'; ++c) {
            std::cout << c << ": ";
            if (showLinks) {
            bool found = false;
            for (const auto& link : player->getLinks()) {
                if (std::tolower(link->getId()) == c) {
                    if (!link->getDownloaded()) {
                        std::cout << (link->getIsVirus() ? "V" : "D") << link->getStrength();
                    }
                    found = true;
                    break;
                }
            }
            if (!found) std::cout << "  ";
            } else {
                std::cout << "?";
            }
            if (c != 'h' && c!= 'd') std::cout << " ";
            else std::cout << std::endl;
        }
    } else {  // Player 2
        for (char c = 'A'; c <= 'H'; ++c) {
            std::cout << c << ": ";
            if (showLinks) {
                bool found = false;
                for (const auto& link : player->getLinks()) {
                    if (std::toupper(link->getId()) == c) {
                        if (!link->getDownloaded()) {
                            std::cout << (link->getIsVirus() ? "V" : "D") 
                                     << link->getStrength();
                        }
                        found = true;
                        break;
                    }
                }
                if (!found) std::cout << "  ";
            } else {
                std::cout << "?";
            }
            if (c != 'H' && c != 'D') std::cout << " ";
            else std::cout << std::endl;
        }
    }
}

void TextObserver::displayBoard() const {
    const auto& players = board->getPlayers();
    if (players.size() < 2) return;
    
    // Display Player 1's info and links (show if Player 1's turn, hide if Player 2's turn)
    displayPlayerInfo(players[0], board->getCurrPlayer() == 0);
    
    std::cout << "========" << std::endl;
    
    // Display board
    for (int i = 0; i < board->getRows(); ++i) {
        for (int j = 0; j < board->getCols(); ++j) {
            Cell* cell = board->getCell(i, j);
            if ((i == 0 && (j == 3 || j == 4)) || 
                (i == 7 && (j == 3 || j == 4))) {
                std::cout << 'S';
            } else if (cell->getLink()) {
                std::cout << cell->getLink()->getId();
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "========";
    
    // Display Player 2's info and links (show if Player 2's turn, hide if Player 1's turn)
    displayPlayerInfo(players[1], board->getCurrPlayer() == 1);
}
