#include "link.h"

class Cell {
    Link* link;
    int row, col;
    bool FirewallOn1, FirewallOn2, hasServerPort, isBlocked;

    public:
        ~Cell();
        bool canOccupy(Link* link) const;
        void setLink(Link* Link);
        Link* getLink();
        // emptyCell() Link* ??
    
};