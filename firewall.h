#include <vector>
#include "ability.h"
using namespace std;

class Firewall : public Ability {
    public:
        void use(Cell *c) override;
        string getName() const override;
};
