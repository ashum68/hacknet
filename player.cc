#include "player.h"
#include <iostream>
using namespace std;

const int WINNING_DATA = 4;
const int LOSING_VIRUSES = 4;

Player::Player(int id) 
    : id{id}, downloadedData{0}, downloadedViruses{0}, usedAbilityThisTurn{false} {}

void Player::addLink(unique_ptr<Link> link) {
    links.push_back(std::move(link));
}

void Player::addAbility(unique_ptr<Ability> ability) {
    abilities.push_back(std::move(ability));
}

bool Player::useAbility(int abilityIndex, Cell* c) {
    if (abilityIndex < 0 || abilityIndex >= abilities.size()) {
        return false;
    }

    auto& ability = abilities[abilityIndex];

    if (ability->getUsed()) {
        return false;
    }
    
    bool result = ability->use(c);

    if (result) {
        ability->setUsed();
    }
    return result;
}

bool Player::downloadLink(int linkIndex) {
    if (linkIndex < 0 || linkIndex >= links.size()) {
        return false;
    }

    auto& link = links[linkIndex];
    if (link->getDownloaded()) return false;

    link->setDownloaded();

    if (link->getIsVirus()) {
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

int Player::getId() const {
    return id;
}

int Player::getDownloadedData() const {
    return downloadedData;
}

void Player::incDownloadedData() {
    downloadedData++;
}

int Player::getDownloadedViruses() const {
    return downloadedViruses;
}

void Player::incDownloadedViruses() {
    downloadedViruses++;
}

const std::vector<std::unique_ptr<Ability>>& Player::getAbilities() const {
    return abilities;
}

const std::vector<std::unique_ptr<Link>>& Player::getLinks() const {
    return links;
}

std::string Player::getName() const { 
    return "Player " + std::to_string(id + 1); 
}
