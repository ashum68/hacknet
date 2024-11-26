#include "cell.h"

Cell::Cell(Link* link, int row, int col)
    : link{link}, row{row}, col{col}, f{}

bool canOccupy(Link* link) const {
    return !link;
}

void setLink(Link* Link) {
    link = Link;
}

Link* getLink() {
    return link;
}

void emptyCell() {
    Link* temp = link;
    link = nullptr;
    delete temp;
}