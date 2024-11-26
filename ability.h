#include "player.h"
#include <vector>
using namespace std;

class Ability {
    bool isUsed;
    public:
        virtual void use(Cell* c);
        virtual string getName() const = 0;
};
