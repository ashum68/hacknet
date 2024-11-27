#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "board.h"
#include "player.h"
#include "ability.h"

using namespace std;

class Game {
    vector<unique_ptr<Player>> players;
    int currplayer;
    unique_ptr<Board> board;

    private:
        static const int MAX_ABILITIES = 5;
        static const int MAX_SAME_ABILITY = 2;
        
        void displayAbilityMenu() const;
        bool isValidAbilityChoice(int choice) const;

    public:
        Game(vector<unique_ptr<Player>> players, unique_ptr<Board> board);
        ~Game();
        
        void start();
        void processCommand(const string& cmd);
        bool isGameOver() const;
        void switchPlayer();
        void initializePlayerAbilities(Player* player);

};

#endif