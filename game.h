#include "board.h"
#include "player.h"
using namsepace std;

class Game {
    // Player* player1, player2;
    vector<Player*> player;
    int currplayer;
    Board* board;

    public:
        Game(vector<Player*> players, Board* board);
        ~Game(); // void? test
        
        void start();
        void processCommand(const string& cmd);
        bool isGameOver() const;
        void switchPlayer();

};