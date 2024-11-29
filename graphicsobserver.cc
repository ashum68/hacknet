#include "graphicsobserver.h"
#include <string>

GraphicsObserver::GraphicsObserver(Game* game) : game{game}, w{800, 900} {}

void GraphicsObserver::renderCell(int r, int c, int cellSize, int boardY) {
    Cell* cell = game->getBoard()->getCell(r, c);
    
    int boardX = (w.getWidth() - 8 * cellSize) / 2;
    int x = boardX + (c * cellSize);
    int y = boardY + (r * cellSize);

    w.fillRectangle(x, y, cellSize, cellSize, Xwindow::LemonChiffon);
    
    w.fillRectangle(x, y, cellSize, 1, Xwindow::Black);
    w.fillRectangle(x, y, 1, cellSize, Xwindow::Black);
    w.fillRectangle(x + cellSize, y, 1, cellSize, Xwindow::Black); 
    w.fillRectangle(x, y + cellSize, cellSize + 1, 1, Xwindow::Black);
    
    if ((r == 0 && (c == 3 || c == 4)) || (r == 7 && (c == 3 || c == 4))) {
        w.fillRectangle(x + 1, y + 1, cellSize - 1, cellSize - 1, Xwindow::Black);
        w.drawString(x + cellSize/3, y + cellSize/2, "S");
        return;
    }
    
    int pieceX = x + pieceOffset;
    int pieceY = y + pieceOffset;
    
    int textX = x + cellSize/2 - 3;
    int textY = y + cellSize/2 + 5;

    if (cell->getLink() && !cell->getLink()->getDownloaded()) {
        Link* link = cell->getLink();
        std::string display(1, link->getId());
        
        if (link->isRevealed() || (link->getOwner() == game->getCurrPlayer())) {
            w.fillRectangle(pieceX - borderWidth, pieceY - borderWidth, pieceSize + 2 * borderWidth, pieceSize + 2 * borderWidth, Xwindow::Black);
            if (link->getIsVirus()) {
                w.fillRectangle(pieceX, pieceY, pieceSize, pieceSize, Xwindow::Red);
            } else {
                w.fillRectangle(pieceX, pieceY, pieceSize, pieceSize, Xwindow::Green);
            }
        }
        if (link->isRevealed() || (link->getOwner() == game->getCurrPlayer())) {
            w.drawString(textX, textY, display);
        } else {
            w.drawString(textX, textY, display);
        }
    } 
    else if (cell->isCellBlocked()) {
        w.drawString(textX, textY, "X");
    } else if (cell->isFirewallOn1()) {
        w.drawString(textX, textY, "w");
    } else if (cell->isFirewallOn2()) {
        w.drawString(textX, textY, "m");
    }
}

void GraphicsObserver::renderPlayerInfo(const Player* player, bool showLinks, int x, int y) {
    std::string header = "Player " + std::to_string(player->getId() + 1) + ":";
    w.drawString(x, y, header);
    
    std::string downloadInfo = "Downloaded: " + std::to_string(player->getDownloadedData()) + "D, " + std::to_string(player->getDownloadedViruses()) + "V";
    w.drawString(x, y + LINE_HEIGHT, downloadInfo);
    
    std::string abilityInfo = "Abilities: ";
    std::vector<std::string> availableAbilityNames;
    int abilityCount = 0;
    for (size_t i = 0; i < player->getAbilities().size(); ++i) {
        const auto& ability = player->getAbilities()[i];
        if (!ability->getUsed()) {
            availableAbilityNames.push_back(std::to_string(i + 1) + " - " + ability->getName());
            abilityCount++;
        }
    }
    
    abilityInfo += std::to_string(abilityCount);
    if (!availableAbilityNames.empty()) {
        abilityInfo += " (";
        for (size_t i = 0; i < availableAbilityNames.size(); ++i) {
            abilityInfo += availableAbilityNames[i];
            if (i < availableAbilityNames.size() - 1) {
                abilityInfo += ", ";
            }
        }
        abilityInfo += ")";
    }
    w.drawString(x, y + LINE_HEIGHT * 2, abilityInfo);
    
    int linkY = y + LINE_HEIGHT * 3;
    int linkX = x;
    
    bool isPlayerOne = player->getId() == 0;
    char startChar = isPlayerOne ? 'a' : 'A';
    char endChar = isPlayerOne ? 'h' : 'H';
    
    for (char c = startChar; c <= endChar; ++c) {
        std::string linkDisplay = std::string(1, c) + ": ";
        
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
                linkDisplay += "--";
            } else if (showLinks) {
                linkDisplay += (targetLink->getIsVirus() ? "V" : "D") + std::to_string(targetLink->getStrength());
            } else {
                linkDisplay += (targetLink->isRevealed() ? (std::string(targetLink->getIsVirus() ? "V" : "D") + std::to_string(targetLink->getStrength())) : "?");
            }
        }
        
        w.drawString(linkX, linkY, linkDisplay);
        linkX += LINK_SPACING;
    }
}

void GraphicsObserver::notify() {
    int windowWidth = w.getWidth();
    int windowHeight = w.getHeight();
    
    w.fillRectangle(0, 0, windowWidth, windowHeight, Xwindow::BlanchedAlmond);
    
    w.drawString((windowWidth / 2) - 50, 30, "RAIInet");

    int boardX = (windowWidth - boardWidth) / 2;
    int boardY = (windowHeight - boardHeight) / 2;
    
    w.fillRectangle(boardX - borderSize, boardY - borderSize, boardWidth + 2*borderSize, boardHeight + 2*borderSize, Xwindow::Sienna);
    
    w.fillRectangle(boardX - borderSize - 1, boardY - borderSize - 1, boardWidth + 2*borderSize + 2, 1, Xwindow::Black);
    w.fillRectangle(boardX - borderSize - 1, boardY - borderSize - 1, 1, boardHeight + 2*borderSize + 2, Xwindow::Black);
    w.fillRectangle(boardX + boardWidth + borderSize, boardY - borderSize - 1, 1, boardHeight + 2*borderSize + 2, Xwindow::Black);
    w.fillRectangle(boardX - borderSize - 1, boardY + boardHeight + borderSize, boardWidth + 2*borderSize + 2, 1, Xwindow::Black);
    
    Board* board = game->getBoard();
    for (int i = 0; i < board->getRows(); ++i) {
        for (int j = 0; j < board->getCols(); ++j) {
            renderCell(i, j, cellSize, boardY);
        }
    }
    
    const auto& players = board->getPlayers();
    if (players.size() >= 2) {
        renderPlayerInfo(players[0], game->getCurrPlayer() == 0, boardX - borderSize, boardY - borderSize - 100);
        renderPlayerInfo(players[1], game->getCurrPlayer() == 1, boardX - borderSize, boardY + boardHeight + borderSize + 30);
    }
}