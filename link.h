#include "player.h"
#include "direction.h"

class Link {
    char id;
    int strength;
    Player* owner;
    int row, col;
    bool revealed, boosted, downloaded, isVirus;

    public:
        virtual ~Link() = default;
        virtual bool isVirus() const = 0;
        
        bool move(Direction dir);
        bool battle(Link* other);
        void reveal();
        char getId() const;
        bool getDownloaded() const;
        void setDownloaded(int newDownloaded);
        int getStrength() const;
        Player* getOwner() const;
};
