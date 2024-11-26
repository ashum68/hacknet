#include "player.h"

const int WINNING_DATA = 4;
const int LOSING_VIRUSES = 4;

Player::Player(const id& id) : id{id}, downloadedData{0}, downloadedViruses{0}, usedAbilityThisTurn{false} {}

void Player::addLink(Link* link) {
    links.push_back(link);
}

void Player::addAbility(Ability* ability) {
    abilities.push_back(ability);
}

bool Player::useAbility(Ability* ability, Cell* c) {
    // ability itself will check if it used properly
    if (!ability || !c) {
        return false;
    }

    return ability->use(c);
}

bool Player::downloadLink(Link* link) {
    if (!link) {
        return false;
    }

    link->setDownloaded(true);

    if (link->isVirus()) {
        setDownloadedViruses(getDownloadedViruses() + 1);
    } else {
        setDownloadedData(getDownloadedData() + 1);
    }

    return true;
}

bool Player::hasWon() const {
    return getDownloadedData() >= WINNING_DATA;
}

bool Player::hasLost() const {
    return getDownloadedViruses() >= LOSING_VIRUSES;
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