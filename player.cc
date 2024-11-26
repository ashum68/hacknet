#include "player.h"

Player::Player(const id& id)
    : id{id}, downloadedData{0}, downloadedViruses{0}, usedAbilityThisTurn{false} {}

void Player::addLink(Link* link) {
    links.push_back(link);
}

void Player::addAbility(Ability* ability) {
    abilities.push_back(ability);
}

bool Player::useAbility(Ability* ability, Cell* c) {
    // if (id < 1 || id > abilities.size()) return false;
    // abilities[id - 1]->use(params);
    // return true;
    
}

bool Player::moveLink(char linkId, Direction dir) { // check if directions valid?
    for (auto link : links) {
        if (link->getId() == linkId) {
            link->move(dir);
            return true;
        }
    }
    return false;
}

string Player::getName() const {
    return name;
}

int Player::getDownloadedData() const {
    return downloadedData;
}

void Player::setDownloadedData(int newDownloaded) {
    downloadedData = newDownloaded;
}

int Player::getDownloadedViruses() const {
    return downloadedViruses;
}

void Player::setDownloadedViruses(int newDownloaded) {
    downloadedViruses = newDownloaded;
}

bool Player::hasWon() const {
    return downloadedData >= 4;
}

bool Player::hasLost() const {
    return downloadedViruses >= 4;
}