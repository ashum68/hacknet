#include <vector>
#include "cell.h"
#include "observer.h"
#include "direction.h"
using namespace std;

class Board {
    vector<vector<Cell*>> grid;
    vector<Observer*> observers;

    public:
        Board();
        ~Board();
        
        // void attach(Observer* obs);
        // void detach(Observer* obs);
        // void notifyObservers();
        
        bool moveLink(Link* link, Direction dir);
        Cell* getCell(int row, int col) const;
        void initializeBoard();
    
};
