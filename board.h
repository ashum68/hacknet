#include <vector>
#include "cell.h"
#include "observer.h"
#include "direction.h"
#include "link.h"
using namespace std;

class Board {
    vector<vector<Cell*>> grid;
    vector<Observer*> observers;

    public:
        void initializeBoard(vector<Player*> players);
        bool moveLink(Link* link, Direction dir);
        Cell* getCell(int row, int col) const;
    
};
