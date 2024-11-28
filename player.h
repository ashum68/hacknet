#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include "link.h"
#include "ability.h"

class Player {
    int id;
    std::vector<std::unique_ptr<Link>> links;
    std::vector<std::unique_ptr<Ability>> abilities;
    int downloadedData, downloadedViruses;
    bool usedAbilityThisTurn;

public:
    Player(int id);
    
    void addLink(std::unique_ptr<Link> link);
    void addAbility(std::unique_ptr<Ability> ability);
    bool useAbility(int abilityIndex, Cell* c = nullptr);
    bool downloadLink(int linkIndex);
    void removeLink(char linkId);
    bool hasWon() const;
    bool hasLost() const;
    
    int getId() const;
    int getDownloadedData() const;
    void incDownloadedData();
    int getDownloadedViruses() const;
    void incDownloadedViruses();
    
    const std::vector<std::unique_ptr<Ability>>& getAbilities() const;
    const std::vector<std::unique_ptr<Link>>& getLinks() const;
    std::string getName() const { return "Player " + std::to_string(id); }
};

#endif // PLAYER_H
