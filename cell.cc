#include "cell.h"

Cell::Cell(Link* link, int row, int col) // default set all to false when created
    : link(link), row(row), col(col),
      firewallOn1(false), firewallOn2(false),
      hasServerPort(false), isBlocked(false) {}

bool Cell::canOccupy(Link* link) const {
    return !isBlocked && link == nullptr;
}

void Cell::setLink(Link* Link) {
    link = Link;
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

// Check if Firewall 1 is active
bool Cell::isFirewallOn1() const {
    return firewallOn1;
}

// Check if Firewall 2 is active
bool Cell::isFirewallOn2() const {
    return firewallOn2;
}

// Activate or deactivate Firewall 1
void Cell::setFirewall1(bool status) {
    firewallOn1 = status;
}

// Activate or deactivate Firewall 2
void Cell::setFirewall2(bool status) {
    firewallOn2 = status;
}

// Check if the cell has a server port
bool Cell::getHasServerPort() const {
    return hasServerPort;
}

// Set the server port status of the cell
void Cell::setHasServerPort(bool status) {
    hasServerPort = status;
}
