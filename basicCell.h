#include "cell.h"

class BasicCell : public Cell {
    public:
        bool canOccupy(Link* link) const override;
        void occupy(Link* link) override;
        void vacate() override;
};