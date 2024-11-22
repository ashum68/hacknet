#include <vector>
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
        void setDownloadedData() const;
        int getDownloadedViruses() const;
        void setDownloadedViruses() const;
        bool hasWon() const;
    
};