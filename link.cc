#include "link.h"

Link::Link(char id, int playerId, int strength, bool revealed = false, bool boosted = false, bool downloaded = false, bool isVirus) : 
    id{id}, playerId{playerId}, strength{strength} {}

bool Link::battle(Link* other) {
    if (strength >= other->getStrength()) {
        other->setDownloaded();
        return true;
    } else if (strength < other->getStrength()) {
        downloaded = true;
        return false;
    }
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
}

int Link::setCol(int c) {
    col = c;
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

void Link::setBoosted() {
    boosted = true;
}

bool Link::isBoosted() const {
    return boosted;
}

int Link::getStrength() const {
    return strength;
}

bool Link::getIsVirus() const {
    return isVirus;
}

char Link::getOwner() const {
    return playerId;
}
