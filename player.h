#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <memory>
#include <string>
#include "ability.h"
#include "link.h"
#include "cell.h"

class Player {
    int id;
    vector<unique_ptr<Link>> links;
    vector<unique_ptr<Ability>> abilities;
    int downloadedData, downloadedViruses;
    bool usedAbilityThisTurn;

public:
    Player(int id);
    
    void addLink(unique_ptr<Link> link);
    void addAbility(unique_ptr<Ability> ability);
    bool useAbility(int abilityIndex, Cell* c);
    bool downloadLink(int linkIndex);
    void removeLink(char linkId);
    bool hasWon() const;
    bool hasLost() const;
    
    int getId() const;
<<<<<<< HEAD
    string getName() const;
=======
>>>>>>> 6c14ee1 (updated .h)
    int getDownloadedData() const;
    void incDownloadedData();
    int getDownloadedViruses() const;
    void incDownloadedViruses();
    
    const vector<unique_ptr<Ability>>& getAbilities() const;
    const vector<unique_ptr<Link>>& getLinks() const;
};

#endif // PLAYER_H
