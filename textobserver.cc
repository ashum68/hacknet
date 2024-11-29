#include "textobserver.h"
#include <iostream>
#include <cctype>
#include <string>

TextObserver::TextObserver(Game* game) : game{game} {}

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
    
    // Determine the case based on player ID
    bool isPlayerOne = player->getId() == 0;
    char startChar = isPlayerOne ? 'a' : 'A';
    char endChar = isPlayerOne ? 'h' : 'H';
    
    for (char c = startChar; c <= endChar; ++c) {
        std::cout << c << ": ";
        
        // Find the corresponding link
        const Link* targetLink = nullptr;
        for (const auto& link : player->getLinks()) {
            if (isPlayerOne) {
                if (std::tolower(link->getId()) == c) {
                    targetLink = link.get();
                    break;
                }
            } else {
                if (std::toupper(link->getId()) == c) {
                    targetLink = link.get();
                    break;
                }
            }
        }
        
        if (targetLink) {
            if (targetLink->getDownloaded()) {
                // Link is captured
                std::cout << "--";
            }
            else if (showLinks) {
                // Link is revealed and not captured
                std::cout << (targetLink->getIsVirus() ? "V" : "D") 
                          << targetLink->getStrength();
            }
            else {
                // Link is hidden and not captured
                std::cout << (targetLink->isRevealed() ? ((targetLink->getIsVirus() ? "V" : "D") + std::to_string(targetLink->getStrength())) : " ?");
            }
        }
        else {
            // No link exists at this position
            std::cout << " ";
        }
        
        // Formatting: add space or newline based on position
        if ((isPlayerOne && (c != 'h' && c != 'd')) || 
            (!isPlayerOne && (c != 'H' && c != 'D'))) {
            std::cout << " ";
        }
        else {
            std::cout << std::endl;
        }
    }
}

void TextObserver::displayBoard() const {
    Board* board = game->getBoard();
    const auto& players = board->getPlayers();
    if (players.size() < 2) return;
    
    // Display Player 1's info and links (show if Player 1's turn, hide if Player 2's turn)
    displayPlayerInfo(players[0], game->getCurrPlayer() == 0);
    
    std::cout << "========" << std::endl;
    
    // Display board
    for (int i = 0; i < board->getRows(); ++i) {
        for (int j = 0; j < board->getCols(); ++j) {
            Cell* cell = board->getCell(i, j);
            if ((i == 0 && (j == 3 || j == 4)) || 
                (i == 7 && (j == 3 || j == 4))) {
                std::cout << 'S';
            } else if (cell->getLink() && !cell->getLink()->getDownloaded()) {
                std::cout << cell->getLink()->getId(); 
            } else if (cell->isCellBlocked()) {
                std::cout << 'X';
            } else if (cell->isFirewallOn1()) {
                std::cout << 'w';
            } else if (cell->isFirewallOn2()) {
                std::cout << 'm';
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    
    std::cout << "========";
    
    // Display Player 2's info and links (show if Player 2's turn, hide if Player 1's turn)
    displayPlayerInfo(players[1], game->getCurrPlayer() == 1);
}
