#include "board.h"
#include "player.h"
using namsepace std;

class Game {
    Player* player1, player2;
    int currplayer;
    Board* board;

    public:
        Game(Player* p1, Player* p2);
        ~Game(); // void? test
        
        void start();
        void processCommand(const string& cmd);
        bool isGameOver() const;
        void switchTurn();

};