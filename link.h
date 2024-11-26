#include "player.h"
#include "direction.h"

class Link {
    char id;
    char playerId;
    int strength;
    int row, col;
    bool revealed, boosted, downloaded, isVirus;

    public:
        // ~Link() = default;
        // bool isVirus() const = 0;
        bool battle(Link* other);
        void reveal();

        char getId() const;
        bool getDownloaded() const;
        // void setDownloaded(int newDownloaded);
        int getStrength() const;
        Player* getOwner() const;
};
