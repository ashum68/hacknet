#include "player.h"
using namespace std;

const int WINNING_DATA = 4;
const int LOSING_VIRUSES = 4;

Player::Player(int id) 
    : id{id}, downloadedData{0}, downloadedViruses{0}, usedAbilityThisTurn{false} {}

void Player::addLink(unique_ptr<Link> link) {
    links.push_back(move(link));
}

void Player::addAbility(unique_ptr<Ability> ability) {
    abilities.push_back(move(ability));
}

bool Player::useAbility(int abilityIndex, Cell* c) {
    if (abilityIndex < 0 || abilityIndex >= abilities.size() || !c) {
        return false;
    }

    auto& ability = abilities[abilityIndex];
    if (ability->getUsed()) {
        return false;
    }

    bool result = ability->use(c);
    if (result) {
        ability->setUsed(true);
    }
    return result;
}

bool Player::downloadLink(int linkIndex) {
    if (linkIndex < 0 || linkIndex >= links.size()) {
        return false;
    }

    auto& link = links[linkIndex];
    link->setDownloaded(true);

    if (link->isVirus()) {
        downloadedViruses++;
    } else {
        downloadedData++;
    }

    return true;
}

bool Player::hasWon() const {
    return downloadedData >= WINNING_DATA;
}

bool Player::hasLost() const {
    return downloadedViruses >= LOSING_VIRUSES;
}

std::string Player::getName() const {
    return "Player " + to_string(id + 1);
}

int Player::getDownloadedData() const {
    return downloadedData;
}

int Player::getDownloadedViruses() const {
    return downloadedViruses;
}

const std::vector<std::unique_ptr<Ability>>& Player::getAbilities() const {
    return abilities;
}

const std::vector<std::unique_ptr<Link>>& Player::getLinks() const {
    return links;
}
