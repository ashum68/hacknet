#include "board.h"
#include <memory>
#include <iostream>

Board::Board() {
    grid.resize(8);
    for (int i = 0; i < 8; i++) {
        grid[i].resize(8);
        for (int j = 0; j < 8; j++) {
            grid[i][j] = std::make_unique<Cell>(nullptr, i, j);
        }
    }
}

void Board::initializeBoard(const std::vector<std::unique_ptr<Player>>& players) {
    this->players.clear();
    for (const auto& player : players) {
        this->players.push_back(player.get());
    }
    
    for (const auto& player : players) {
        for (const auto& link : player->getLinks()) {
            int row = link->getRow();
            int col = link->getCol();
            Cell* targetCell = grid[row][col].get();
            targetCell->setLink(link.get());
        }
    }

    grid[0][3]->setServerPort(1); 
    grid[0][4]->setServerPort(1);
    grid[7][3]->setServerPort(2);
    grid[7][4]->setServerPort(2);
}

bool Board::moveLink(Link* link, Direction dir) {

    if (!link) {
        std::cerr << "Error: Attempted to move a null Link pointer.\n";
        return false;
    }

    int row = link->getRow();
    int col = link->getCol();
    int newRow = row;
    int newCol = col;
    
    switch (dir) {
        case Direction::UP:
            newRow--;
            break;
        case Direction::DOWN:
            newRow++;
            break;
        case Direction::LEFT:
            newCol--;
            break;
        case Direction::RIGHT:
            newCol++;
            break;
        default:
            std::cerr << "Error: Invalid direction provided for moving Link ID: " 
                      << link->getId() << ".\n";
            return false;
    }

    if (newRow < 0 || newRow >= grid.size() || newCol < 0 || newCol >= grid[0].size()) {
        return false;
    }

    Cell* newCell = grid[newRow][newCol].get();
    if (newCell->canOccupy(link)) {
        if (newCell->getServerPort()) {
            Player* opponent = players[newCell->getServerPort() - 1];
            link->getIsVirus() ? opponent->incDownloadedViruses() : opponent->incDownloadedData();
            link->setDownloaded();
            grid[row][col]->emptyCell();
            grid[newRow][newCol]->emptyCell();
            return true;
        }

        if (newCell->getLink()) {
            int opponentIndex = newCell->getLink()->getOwner();
            Player* opponent = players[opponentIndex];
            bool battleResult = link->battle(newCell->getLink());
            if (battleResult) { // if you won - download what opponent has
                newCell->getLink()->getIsVirus() ? players[currentPlayer]->incDownloadedViruses() : players[currentPlayer]->incDownloadedData();
                grid[row][col]->emptyCell();
                newCell->setLink(link);
                link->setRow(newRow);
                link->setCol(newCol);
                if (newCell->isFirewallOn1() && currentPlayer == 0) {
                    link->reveal();
                    std::cout << "FIREWALL ON 1 AFTER BATTLE REVEALED" << std::endl;
                } else if (newCell->isFirewallOn2() && currentPlayer == 1) {
                    link->reveal();
                    std::cout << "FIREWALL ON 2 AFTER BATTLE REVEALED" << std::endl;
                }
                return true;
            } else { // if you LOST
                link->getIsVirus() ? opponent->incDownloadedViruses() : opponent->incDownloadedData();
                grid[row][col]->emptyCell();
                return true;
            }
        }
        if (newCell->isFirewallOn1()) {
            std::cout << "TEST FIREWALL ON 1" << std::endl;
            if (!newCell->getLink()) { // Check if link exists
                int opponentIndex = link->getOwner() ? 0 : 1;
                if (opponentIndex == 1) {
                    link->reveal();
                    std::cout << link->getId() << " has been revealed" << std::endl;
                }
            }
        } else if (newCell->isFirewallOn2()) {
            std::cout << "TEST FIREWALL ON 2" << std::endl;
            if (!newCell->getLink()) { // Check if link exists
                int opponentIndex = link->getOwner() ? 0 : 1;
                if (opponentIndex == 0) {
                    link->reveal();
                    std::cout << link->getId() << " has been revealed" << std::endl;
                }

            }
        }
        grid[row][col]->emptyCell();
        newCell->setLink(link);
        link->setRow(newRow);
        link->setCol(newCol);
        return true;
    }
    return false;
}

Cell* Board::getCell(int row, int col) const {
    return grid[row][col].get();
}

// void Board::attach(Observer* obs) {
//     observers.push_back(obs);
// }

void Board::display() const {
    for (int i = 0; i < getRows(); ++i) {
        for (int j = 0; j < getCols(); ++j) {
            Cell* cell = getCell(i, j);
            if ((i == 0 && (j == 3 || j == 4)) || 
                (i == 7 && (j == 3 || j == 4))) {
                std::cout << 'S';
            } else if (cell->getLink()) {
                std::cout << cell->getLink()->getId();
            } else if (cell->isCellBlocked()) {
                std::cout << 'X';
            } else if (cell->isFirewallOn1()) {
                std::cout << 'y';
            } else if (cell->isFirewallOn2()) {
                std::cout << 'Y';
            } else {
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
}
