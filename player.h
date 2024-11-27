#include <vector>
#include "ability.h"
#include "link.h"
#include "direction.h"
using namespace std;

class Player {
    char id;
    vector<Link*> links;
    vector<Ability*> abilities;
    int downloadedData, downloadedViruses;
    bool usedAbilityThisTurn;

    public:
        Player(const char& id);
        
        void addLink(Link* link);
        vector<Link*> getLinks() const;
        void addAbility(Ability* ability);
        bool useAbility(Ability* ability, Cell* c);
        bool downloadLink(Link* link); 
        bool hasWon() const;
        bool hasLost() const;
        
        string getName() const;
        int getDownloadedData() const;
        void setDownloadedData(int newDownloaded);
        int getDownloadedViruses() const;
        void setDownloadedViruses(int newDownloaded);
    
};