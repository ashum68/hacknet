#include <vector>
#include "ability.h"
using namespace std;

class LinkBoost : public Ability {
    public:
        void use(Cell *c) override;
        string getName() const override;
};
