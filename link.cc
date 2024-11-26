#include "link.h"

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

bool isBoosted() const {
    return boosted;
}

int Link::getStrength() const {
    return strength;
}

char Link::getOwner() const {
    return playerId;
}
