#include "board.h"
#include "player.h"
using namsepace std;

class Game {
    // Player* player1, player2;
    vector<Player*> players;
    int currplayer;
    Board* board;

    private:
        static const int MAX_ABILITIES = 5;
        static const int MAX_SAME_ABILITY = 2;
        
        void displayAbilityMenu() const;
        bool isValidAbilityChoice(int choice) const;

    public:
        Game(vector<Player*> players, Board* board);
        ~Game(); // void? test
        
        void start();
        void processCommand(const string& cmd);
        bool isGameOver() const;
        void switchPlayer();
        void initializePlayerAbilities(Player* player);

};