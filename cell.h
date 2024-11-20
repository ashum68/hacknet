#include "link.h"

class Cell {
    Link* link;
    int row, col;

    public:
        virtual ~Cell() = default;
        virtual bool canOccupy(Link* link) const = 0;
        virtual void setLink(Link* link) = 0;
        virtual Link* getLink() const = 0;
    
};