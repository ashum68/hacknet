#include <vector>
#include "player.h"
#include "ability.h"
#include "link.h"
#include "direction.h"
using namespace std;

class Player {
    string name;
    vector<Link*> links;
    vector<Ability*> abilities;
    int downloadedData, downloadedViruses;

    public:
        Player(const string& name);
        
        void addLink(Link* link);
        void addAbility(Ability* ability);
        bool useAbility(int id, const vector<int>& params);
        bool moveLink(char linkId, Direction dir);
        
        int getDownloadedData() const;
        int getDownloadedViruses() const;
        bool hasWon() const;
    
};