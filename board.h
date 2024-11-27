#include <vector>
#include "cell.h"
#include "observer.h"
#include "direction.h"
#include "link.h"
#include "player.h"
using namespace std;

class Board {
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;
    std::vector<Observer*> observers;

    public:
<<<<<<< HEAD
        void initializeBoard(vector<Player*> players);
=======
        Board::Board();
        void initializeBoard(const vector<unique_ptr<Player>>& players);
>>>>>>> 85fd2a2697041c0c3aa38847cf875ba4f1b6eb5e
        bool moveLink(Link* link, Direction dir);
        Cell* getCell(int row, int col) const;
    
};
