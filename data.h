#include "link.h"

class Data : public Link {
    public:
        Data(char id, int strength, Player* owner);
        bool isVirus() const override;
};