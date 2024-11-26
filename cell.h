#include "link.h"

class Cell {
    Link* link;
    int row, col;
    bool FirewallOn1, FirewallOn2, hasServerPort, isBlocked;

    public:
        // virtual ~Cell() = default;
        // virtual bool canOccupy(Link* link) const = 0;
        // virtual void setLink(Link* link) = 0;
        // virtual Link* getLink() const = 0;

        ~Cell();
        bool canOccupy(Link* link) const;
        void setLink(Link* Link);
        Link* getLink();

        // emptyCell() Link* ??
    
};