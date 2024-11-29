#include "graphicsobserver.h"
#include <string>

GraphicsObserver::GraphicsObserver(Game* game) : game{game}, w{800, 900} {}

void GraphicsObserver::renderCell(int r, int c, int cellSize, int boardY) {
    Cell* cell = game->getBoard()->getCell(r, c);
    
    // Calculate position with centered board
    int boardX = (w.getWidth() - 8 * cellSize) / 2;
    int x = boardX + (c * cellSize);
    int y = boardY + (r * cellSize);

    // Default background (white)
    w.fillRectangle(x, y, cellSize, cellSize, Xwindow::LemonChiffon);
    
    // Draw cell borders (black)
    w.fillRectangle(x, y, cellSize, 1, Xwindow::Black);  // Top
    w.fillRectangle(x, y, 1, cellSize, Xwindow::Black);  // Left
    w.fillRectangle(x + cellSize, y, 1, cellSize, Xwindow::Black);  // Right
    w.fillRectangle(x, y + cellSize, cellSize + 1, 1, Xwindow::Black);  // Bottom
    
    // Server ports (black squares with 'S')
    if ((r == 0 && (c == 3 || c == 4)) || (r == 7 && (c == 3 || c == 4))) {
        w.fillRectangle(x + 1, y + 1, cellSize - 1, cellSize - 1, Xwindow::Black);
        w.drawString(x + cellSize/3, y + cellSize/2, "S");
        return;
    }
    
    // Calculate piece size and position (smaller than cell)
    const int pieceSize = cellSize * 2/3;  // Piece is 2/3 the size of cell
    const int pieceOffset = (cellSize - pieceSize) / 2;  // Center the piece
    int pieceX = x + pieceOffset;
    int pieceY = y + pieceOffset;
    const int borderWidth = 1;  // Width of the piece's border
    
    // Calculate centered text position within piece
    int textX = x + cellSize/2 - 3;  // Subtract half character width
    int textY = y + cellSize/2 + 5;  // Add half character height
    
    // Render link if present
    if (cell->getLink() && !cell->getLink()->getDownloaded()) {
        Link* link = cell->getLink();
        std::string display(1, link->getId());
        
        if (link->isRevealed() || (link->getOwner() == game->getCurrPlayer())) {
            // Draw black border first
            w.fillRectangle(pieceX - borderWidth, pieceY - borderWidth, 
                           pieceSize + 2*borderWidth, pieceSize + 2*borderWidth, 
                           Xwindow::Black);
            
            // Then draw the colored piece inside
            if (link->getIsVirus()) {
                w.fillRectangle(pieceX, pieceY, pieceSize, pieceSize, Xwindow::Red);
            } else {
                w.fillRectangle(pieceX, pieceY, pieceSize, pieceSize, Xwindow::Green);
            }
        }
        // Draw text in white if piece is colored, black otherwise
        if (link->isRevealed() || (link->getOwner() == game->getCurrPlayer())) {
            w.drawString(textX, textY, display);
        } else {
            w.drawString(textX, textY, display);
        }
    } 
    // Render cell states
    else if (cell->isCellBlocked()) {
        w.drawString(textX, textY, "X");
    } else if (cell->isFirewallOn1()) {
        w.drawString(textX, textY, "w");
    } else if (cell->isFirewallOn2()) {
        w.drawString(textX, textY, "m");
    }
}

void GraphicsObserver::renderPlayerInfo(const Player* player, bool showLinks, int x, int y) {
    // Increase font spacing
    const int LINE_HEIGHT = 30;  // Keep existing spacing
    const int LINK_SPACING = 60; // Space between each link
    
    // Display player header and downloaded info
    std::string header = "Player " + std::to_string(player->getId() + 1) + ":";
    w.drawString(x, y, header);
    
    std::string downloadInfo = "Downloaded: " + std::to_string(player->getDownloadedData()) + "D, " 
                              + std::to_string(player->getDownloadedViruses()) + "V";
    w.drawString(x, y + LINE_HEIGHT, downloadInfo);
    
    // Count and display available abilities with names
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
    
    // Add ability names to display string
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
    
    // Display link information in one line
    int linkY = y + LINE_HEIGHT * 3;
    int linkX = x;
    
    // Determine link display range based on player
    bool isPlayerOne = player->getId() == 0;
    char startChar = isPlayerOne ? 'a' : 'A';
    char endChar = isPlayerOne ? 'h' : 'H';
    
    for (char c = startChar; c <= endChar; ++c) {
        std::string linkDisplay = std::string(1, c) + ": ";
        
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
                linkDisplay += "--";
            } else if (showLinks) {
                linkDisplay += (targetLink->getIsVirus() ? "V" : "D") + 
                             std::to_string(targetLink->getStrength());
            } else {
                linkDisplay += (targetLink->isRevealed() ? 
                    (std::string(targetLink->getIsVirus() ? "V" : "D") + 
                     std::to_string(targetLink->getStrength())) : "?");
            }
        }
        
        w.drawString(linkX, linkY, linkDisplay);
        linkX += LINK_SPACING;  // Move to next position horizontally
    }
}

void GraphicsObserver::notify() {
    const int windowWidth = w.getWidth();
    const int windowHeight = w.getHeight();
    const int cellSize = 65;  // Increased from 50
    const int boardWidth = 8 * cellSize;
    const int boardHeight = 8 * cellSize;
    const int borderSize = 30;  // Increased from 20
    
    // Antique parchment background (soft beige)
    w.fillRectangle(0, 0, windowWidth, windowHeight, Xwindow::BlanchedAlmond);
    
    // Draw title
    w.drawString(windowWidth/2 - 50, 30, "RAIInet");
    
    // Calculate board position to center it
    int boardX = (windowWidth - boardWidth) / 2;
    int boardY = (windowHeight - boardHeight) / 2;
    
    // Draw Sienna background with border
    w.fillRectangle(boardX - borderSize, boardY - borderSize, 
                    boardWidth + 2*borderSize, boardHeight + 2*borderSize, 
                    Xwindow::Sienna);
    
    // Draw black outline around Sienna border
    w.fillRectangle(boardX - borderSize - 1, boardY - borderSize - 1, 
                    boardWidth + 2*borderSize + 2, 1, Xwindow::Black);  // Top
    w.fillRectangle(boardX - borderSize - 1, boardY - borderSize - 1, 
                    1, boardHeight + 2*borderSize + 2, Xwindow::Black);  // Left
    w.fillRectangle(boardX + boardWidth + borderSize, boardY - borderSize - 1, 
                    1, boardHeight + 2*borderSize + 2, Xwindow::Black);  // Right
    w.fillRectangle(boardX - borderSize - 1, boardY + boardHeight + borderSize, 
                    boardWidth + 2*borderSize + 2, 1, Xwindow::Black);  // Bottom
    
    // Draw board
    Board* board = game->getBoard();
    for (int i = 0; i < board->getRows(); ++i) {
        for (int j = 0; j < board->getCols(); ++j) {
            renderCell(i, j, cellSize, boardY);  // Use boardY instead of fixed offset
        }
    }
    
    // Update player information positions with more spacing
    const auto& players = board->getPlayers();
    if (players.size() >= 2) {
        // Player 1 info (top of board)
        renderPlayerInfo(players[0], game->getCurrPlayer() == 0, 
                        boardX - borderSize, boardY - borderSize - 100);  // Increased spacing
        
        // Player 2 info (bottom of board)
        renderPlayerInfo(players[1], game->getCurrPlayer() == 1, 
                        boardX - borderSize, boardY + boardHeight + borderSize + 30);  // Increased spacing
    }
}

void GraphicsObserver::renderAbilitiesDisplay() {
    const int startX = 50;
    const int startY = 50;
    const int lineHeight = 30;
    
    // Clear the window
    w.fillRectangle(0, 0, w.getWidth(), w.getHeight(), Xwindow::BlanchedAlmond);
    
    // Display header
    w.drawString(startX, startY, "Available Abilities:");
    
    // Get current player's abilities
    const auto& abilities = game->getPlayer(game->getCurrPlayer())->getAbilities();
    
    // Display each ability
    int currentY = startY + lineHeight;
    for (size_t i = 0; i < abilities.size(); ++i) {
        std::string abilityText = std::to_string(i + 1) + ". " + abilities[i]->getName() + 
                                 " - " + (abilities[i]->getUsed() ? "Used" : "Available");
        w.drawString(startX, currentY, abilityText);
        currentY += lineHeight;
    }
    
    // Display instruction at bottom
    w.drawString(startX, currentY + lineHeight, 
                "Press any key to return to game...");
}
