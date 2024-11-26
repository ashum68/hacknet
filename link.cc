#include "link.h"

void Link::reveal() {
    revealed = true;
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
