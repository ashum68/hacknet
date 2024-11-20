#include "cell.h"
#include "player.h"

class ServerPort : public Cell {
    Player* owner;
    
    public:
        bool canOccupy(Link* link) const override;
        void occupy(Link* link) override;
        void vacate() override;
};