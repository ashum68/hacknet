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
        
        string getName() const;
        int getDownloadedData() const;
        void setDownloadedData(int newDownloaded);
        int getDownloadedViruses() const;
        void setDownloadedViruses(int newDownloaded);
        bool hasWon() const;
        bool hasLost() const;
    
};