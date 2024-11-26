#include "link.h"

// bool Link::move(Direction dir) {
//     // works if we rotate the board every time, time complexity issue? Or does it 
//     switch (dir) {
//         case Direction::UP:
//             row--;
//             break;
//         case Direction::DOWN:
//             row++;
//             break;
//         case Direction::LEFT:
//             col--;
//             break;
//         case Direction::RIGHT:
//             col++;
//             break;
//         default:
//             return false;
//     }

//     if (row < 0 || row >= 8 || col < 0 || col >= 8) { // adjust 8 for size depending on # of players
//         return false;
//     }
//     return true;
// }

bool Link::battle(Link* other) {
    // if data vs data, return false if you lost, true if you won
   if (this->strength > other.strength) {
    return true;
   } else if (strength < other->strength) {
    return false;
   } else {
    return true;
   }
}

void Link::reveal() {
    revealed = true;
}

char Link::getId() const {
    return id;
}

bool Link::getDownloaded() const {
    return downloaded;
}

// void setDownloaded(int newDownloaded) {
//     // implement
// }

int Link::getStrength() const {
    return strength;
}

Player* Link::getOwner() const {
    return owner;
}
