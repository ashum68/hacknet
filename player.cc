#include "player.h"

void Player::addLink(Link* link) {
    links.push_back(link)
}

void Player::addAbility(Ability* ability) {
    abilities.push_back(ability);
}

bool Player::useAbility(int id, const vector<int>& params) {
    if (id < 1 || id > abilities.size()) return false;
    abilities[id - 1]->use(params);
    return true;
}

bool Player::moveLink(char linkId, Direction dir) {
    for (auto link : links) {
        if (link->getId() == linkId) {
            link->move(dir);
            return true;
        }
    }
    return false;
}

int Player::getDownloadedData() const {
    return downloadedData;
}

void Player::setDownloadedData(int newDownloaded) const {
    downloadedData = newDownloaded;
}

int Player::getDownloadedViruses() const {
    return downloadedViruses;
}

bool Player::hasWon() const {
    return downloadedData >= 4;
}
