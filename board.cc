#include "board.h"
#include "direction.h"
#include <iostream>

Board::Board() {
    grid.resize(8, std::vector<std::unique_ptr<Cell>>(8));
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = std::make_unique<Cell>(nullptr, i, j);
        }
    }
}

void Board::initializeBoard(const std::vector<std::unique_ptr<Player>>& players) {
    for (const auto& player : players) {
        for (const auto& link : player->getLinks()) { // Assuming Player::getLinks() returns const std::vector<std::unique_ptr<Link>>&
            int row = link->getRow();
            int col = link->getCol();

            Cell* targetCell = grid[row][col].get();
            targetCell->setLink(link.get());
        }
    }
}

void Board::initializeBoard(vector<Player*> players) {
    for (int i = 0; i < players.size(); i++) {
        vector<Link*> links = players[i]->getLinks();
        for (int j = 0; j < links.size(); j++) {
            grid[links[j]->getRow()][links[j]->getCol()]->setLink(links[j]);
        }
    }
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
