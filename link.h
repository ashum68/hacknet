#ifndef LINK_H
#define LINK_H

#include "player.h"
#include "direction.h"

class Link {
    char id, playerId;
    int strength, row, col;
    bool revealed, boosted, downloaded, isVirus;

public:
    bool battle(Link* other);
    void reveal();

    char getId() const;
    bool getDownloaded() const;
    void setDownloaded();
    void setBoosted();
    bool isBoosted() const;
    int getStrength() const;
    char getOwner() const;
};

#endif