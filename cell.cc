#include "cell.h"

Cell::Cell(Link* link, int row, int col) // default set all to false when created
    : link(link), row(row), col(col),
      firewallOn1(false), firewallOn2(false),
      hasServerPort(false), isBlocked(false) {}

bool Cell::canOccupy(Link* link) const {
    return !isBlocked && this->link == nullptr;
}

void Cell::setLink(Link* newLink) {
    link = newLink;
}

int Cell::getRow() const {
    return row;
}

int Cell::getCol() const {
    return col;
}

Link* Cell::getLink() const {
    return link;
}

void Cell::emptyCell() {
    link = nullptr;
}

bool Cell::isCellBlocked() const {
    return isBlocked;
}

void Cell::setBlocked(bool blocked) {
    isBlocked = blocked;
}

bool Cell::isFirewallOn1() const {
    return firewallOn1;
}

bool Cell::isFirewallOn2() const {
    return firewallOn2;
}

void Cell::setFirewall1() {
    firewallOn1 = true;
}

void Cell::setFirewall2() {
    firewallOn2 = true;
}

bool Cell::getHasServerPort() const {
    return hasServerPort;
}

void Cell::setHasServerPort(bool status) {
    hasServerPort = status;
}
