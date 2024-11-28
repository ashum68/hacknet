#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <map>
#include "player.h"
#include "ability.h"
#include "subject.h"
#include "board.h"

class TextObserver;  // Forward declaration

using namespace std;

class Game : public Subject {
    vector<unique_ptr<Player>> players;
    int currplayer;
    unique_ptr<Board> board;
    map<string, int> abilityCount;
    int abilitiesChosen = 0;
    int choice;
    Observer* textObserver;  // Change to raw pointer

    private:
        static const int MAX_ABILITIES = 5;
        static const int MAX_SAME_ABILITY = 2;
        
        void displayAbilityMenu() const;
        bool isValidAbilityChoice(int choice) const;
        vector<string> split(const string& str) const;
        string toLower(const string& str) const;

    public:
        Game(vector<unique_ptr<Player>> players);
        ~Game();  // Add destructor declaration
        
        void start();
        void run();
        void processCommand(const string& cmd);
        bool isGameOver() const;
        void switchPlayer();
        void initializePlayerAbilities(Player* player);
        int getCurrPlayer() const;
        Player* getPlayer(int id) const;
        Board* getBoard() const;
        void notifyObservers() override;
};

#endif