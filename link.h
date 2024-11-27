#ifndef LINK_H
#define LINK_H

#include "player.h"
#include "direction.h"

class Link {
    char id;
    int playerId, strength, row, col;
    bool revealed, boosted, downloaded, isVirus;

public:
    Link(char id, int playerId, int strength, bool revealed = false, bool boosted = false, bool downloaded = false, bool isVirus);
    bool battle(Link* other);
    void reveal();

    char getId() const;
    bool getDownloaded() const;
    void setDownloaded();
    void setBoosted();
    void setRow();
    void setCol();
    bool isBoosted() const;
    int getStrength() const;
    int getRow() const;
    int getCol() const;
    int setRow(int r);
    int setCol(int c);
    char getOwner() const;
};

#endif