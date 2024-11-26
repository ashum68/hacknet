#ifndef POLARIZE_H
#define POLARIZE_H
#include <vector>
#include "ability.h"
using namespace std;

class Polarize : public Ability {
    public:
        void use(const vector<int>& params) override;
        string getName() const override;
};

#endif
