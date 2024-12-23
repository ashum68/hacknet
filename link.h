#ifndef LINK_H
#define LINK_H

class Link {
    char id;
    int playerId;
    int strength;
    bool revealed;
    int boosted;
    bool downloaded;
    bool isVirus;
    int row;
    int col;

public:
    Link(char id, int playerId, int strength, bool isVirus, int row, int col);
    
    bool battle(Link* other);
    void reveal();

    // getters
    int getRow() const;
    int getCol() const;
    char getId() const;
    bool getDownloaded() const;
    int getBoosted() const;
    int getStrength() const;
    bool getIsVirus() const;
    int getOwner() const;
    bool isRevealed() const;

    // setters
    int setRow(int r);
    int setCol(int c);
    void setDownloaded();
    void addBoosted();
    void decStrength();
    void setVirus();
};

#endif
