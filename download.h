#include <vector>
#include "ability.h"
using namespace std;

class Download : public Ability {
    public:
        void use(const vector<int>& params) override;
        string getName() const override;
};
