#include "player.h"
#include "direction.h"

class Link {
    char id;
    int strength;
    Player* owner;
    bool revealed, boosted;

    public:
        virtual ~Link() = default;
        virtual bool isVirus() const = 0;
        
        bool move(Direction dir);
        bool battle(Link* other);
        void reveal();
        char getId() const;
        int getStrength() const;
        Player* getOwner() const;
};
