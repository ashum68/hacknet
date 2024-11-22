#include "player.h"
#include <vector>
using namespace std;

class Ability {
    public:
        virtual void use(Cell* c1, Cell* c2) = 0;
        virtual string getName() const = 0;
};