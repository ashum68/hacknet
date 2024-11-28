#include "cell.h"
#include "link.h"

Cell::Cell(Link* link, int row, int col) // default set all to false when created
    : link(link), row(row), col(col),
      firewallOn1(false), firewallOn2(false),
      hasServerPort(false), isBlocked(false) {}

bool Cell::canOccupy(Link* incomingLink) const {
    if (isBlocked) return false;
    
    // If cell is empty, allow movement
    if (this->link == nullptr) return true;
    
    // If there's a link in the cell
    if (incomingLink && this->link) {
        // Don't allow moving into your own link
        if (incomingLink->getOwner() == this->link->getOwner()) {
            return false;
        }
        // Allow moving into opponent's link (battle will occur)
        return true;
    }
    
    return false;
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
