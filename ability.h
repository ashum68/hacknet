#include "player.h"
#include <vector>
using namespace std;

class Ability {
    bool used = false;
    Player* owner;

    public:
        virtual ~Ability() = default;
        virtual void use(const vector<int>& params) = 0;
        virtual string getName() const = 0;
    
};