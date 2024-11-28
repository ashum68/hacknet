#include "link.h"

Link::Link(char id, int playerId, int strength, bool isVirus, int row, int col) : 
    id{id}, 
    playerId{playerId}, 
    strength{strength},
    revealed{false},
    boosted{0},
    downloaded{false},
    isVirus{isVirus},
    row{row},
    col{col} {}

bool Link::battle(Link* other) {
    if (strength >= other->getStrength()) {
        other->setDownloaded();
        return true;
    } else if (strength < other->getStrength()) {
        downloaded = true;
        return false;
    }
    return false;
}

void Link::reveal() {
    revealed = true;
} 

int Link::getRow() const {
    return row;
}

int Link::getCol() const {
    return col;
}

int Link::setRow(int r) {
    row = r;
    return row;
}

int Link::setCol(int c) {
    col = c;
    return col;
}

char Link::getId() const {
    return id;
}

void Link::setDownloaded() {
    downloaded = true;
}

bool Link::getDownloaded() const {
    return downloaded;
}

void Link::addBoosted() {
    boosted++;
}

int Link::getBoosted() const {
    return boosted;
}

int Link::getStrength() const {
    return strength;
}

bool Link::getIsVirus() const {
    return isVirus;
}

void Link::setVirus() {
    isVirus = !isVirus;
}

char Link::getOwner() const {
    return playerId;
}

bool Link::isRevealed() const {
    return revealed;
}