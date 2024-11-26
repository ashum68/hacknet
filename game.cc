#include <iostream>
#include <map>
#include "game.h"
#include "link.h"
#include "player.h"

using namespace std;

Game::Game(vector<Player*> players, Board* board):
    player(players), currplayer(0), board(board) {}

void Game::start() {

    cout << "How many players are playing, 2 or 4?" << endl;
    int numPlayers = 0;

    while (numPlayers != 2 && numPlayers != 4) {
        cout << "Enter number of players: ";
        cin >> numPlayers;
        if (numPlayers != 2 && numPlayers != 4) {
            cout << "Invalid number of players. Please enter 2 or 4." << endl;
        }
    }

    player.resize(numPlayers); // either size of 2 or 4 now
    
    for (int i = 0; i < player.size(); i++) { // add shit to both players links and abilitiies
        // init map for letters that are filled
        map<char, bool> occupied;

        if (i == 0) {
            occupied['a'] = false;
            occupied['b'] = false;
            occupied['c'] = false;
            occupied['d'] = false;
            occupied['e'] = false;
            occupied['f'] = false;
            occupied['g'] = false;
            occupied['h'] = false;
        } else if (i == 1) {
            occupied['A'] = false;
            occupied['B'] = false;
            occupied['C'] = false;
            occupied['D'] = false;
            occupied['E'] = false;
            occupied['F'] = false;
            occupied['G'] = false;
            occupied['H'] = false;
        }
        
        player[i] = new Player(i);
        cout << "Player " << i << "'s turn." << endl;

        for (int j = 0; j < 4; j++) { // adding data 1-4
            cout << "Choose position a-h for D" << j << ":" << endl;
            char pos;
            cin >> pos;
            while (pos < 'a' || pos > 'h' || occupied[pos]) {
                cout << "Invalid position. Please enter a non-occupied or valid position." << endl;
                cin >> pos;
            }
            Link* newLink = new Link(pos, i, j, false);
            player[i]->addLink(newLink);
            occupied[pos] = true;
        }

        for (int j = 0; j < 4; j++) { // adding virus 1-4
            cout << "Choose position a-h for V" << j << ":" << endl;
            char pos;
            cin >> pos;
            while (pos < 'a' || pos > 'h' || occupied[pos]) {
                cout << "Invalid position. Please enter a non-occupied or valid position." << endl;
                cin >> pos;
            }
            Link* newLink = new Link(pos, i, j, true);
            player[i]->addLink(newLink);
            occupied[pos] = true;
        }


    }
}

void Game::processCommand(const string& cmd) {
    // Implementation here
}

bool Game::isGameOver() const {
    // Implementation here
}

void Game::switchPlayer() {
    // Implementation here
}


