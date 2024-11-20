#include "link.h"

class Virus : public Link {
    public:
        Virus(char id, int strength, Player* owner);
        bool isVirus() const override;
};