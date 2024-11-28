#ifndef LINK_H
#define LINK_H

#include "player.h"
#include "direction.h"

class Link {
    char id;
    int playerId, strength, row, col, boosted;
    bool revealed, downloaded, isVirus;

public:
    Link(char id, int playerId, int strength, bool revealed = false, int boosted = 0, bool downloaded = false, bool isVirus);
    bool battle(Link* other);
    void reveal();

    char getId() const;
    bool getDownloaded() const;
    void setDownloaded();
    bool isRevealed() const;
    void setRevealed();
    void addBoosted();
    int getBoosted() const;
    int getStrength() const;
    int getRow() const;
    int getCol() const;
    bool getIsVirus() const;
    void setVirus();
    int setRow(int r);
    int setCol(int c);
    char getOwner() const;
};

#endif