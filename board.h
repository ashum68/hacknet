#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "cell.h"
#include "observer.h"
#include "direction.h"
#include "link.h"
#include "player.h"

class Board {
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;
    std::vector<Observer*> observers;
    std::vector<Player*> players;
    int currentPlayer = 0;

    public:
        Board();
        void initializeBoard(const std::vector<std::unique_ptr<Player>>& players);
        bool moveLink(Link* link, Direction dir);
        Cell* getCell(int row, int col) const;
        void attach(Observer* obs);
        void detach(Observer* obs);
        void notifyObservers();
        int getRows() const { return grid.size(); }
        int getCols() const { return grid[0].size(); }
        void display() const;
        const std::vector<Player*>& getPlayers() const { return players; }
        void setCurrentPlayer(int player) { currentPlayer = player; }
        int getCurrPlayer() const { return currentPlayer; }
};

#endif
