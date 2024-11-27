#ifndef CELL_H
#define CELL_H

#include "link.h"
#include <string>

using namespace std;

class Cell {
    Link* link;
    int row, col;
    bool firewallOn1, firewallOn2, hasServerPort, isBlocked;

    public:
        Cell(Link* link, int row, int col);
        ~Cell() = default;
        bool canOccupy(Link* link) const;
        void setLink(Link* Link);
        int getRow() const;
        int getCol() const;
        Link* getLink() const;
        void emptyCell();

            
        // for abilities
        bool isCellBlocked() const;
        void setBlocked(bool blocked);
        bool isFirewallOn1() const;
        bool isFirewallOn2() const;
        void setFirewall1(bool status);
        void setFirewall2(bool status);
        bool getHasServerPort() const;
        void setHasServerPort(bool status);
    
};

#endif
