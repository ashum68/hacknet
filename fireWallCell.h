#include "cell.h"
#include "player.h"

class FireWall : public Cell {
    Player* owner;
    
    public:
        bool canOccupy(Link* link) const override;
        void occupy(Link* link) override;
        void vacate() override;
};