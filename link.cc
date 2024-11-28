#include "link.h"

Link::Link(char id, int playerId, int strength, bool revealed = false, int boosted = 0, bool downloaded = false, bool isVirus) : 
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

bool Link::isRevealed() const {
    return revealed;
}

void Link::setRevealed() {
    revealed = true;
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

void Link::setStrength(int s) {
    if (s > 0) strength = s;
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