#include "board.h"
#include "direction.h"

void initializeBoard(vector<unique_ptr<Player>> players) {
    // impl
}

bool Board::moveLink(Link* link, Direction dir) {
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
    }

    if (newRow < 0 || newRow >= grid.size() || newCol < 0 || newCol >= grid[0].size()) {
        return false;
    }

    Cell* newCell = grid[newRow][newCol];
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
    return grid[row][col];
}