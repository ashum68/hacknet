#include <vector>
#include "cell.h"
#include "observer.h"
#include "direction.h"
using namespace std;

class Board {
    vector<vector<Cell*>> grid;
    vector<Observer*> observers;

    public:
        
        bool moveLink(Link* link, Direction dir);
        Cell* getCell(int row, int col) const;
    
};
