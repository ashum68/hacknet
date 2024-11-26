#include "game.h"

using namespace std;

Game::Game(vector<Player*> players, Board* board):
    player(players), currplayer(0), board(board) {}

void Game::start() {

    cout << "How many players? 2 or 4 players only." << endl;
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
        player[i] = new Player(i);
        cout << "Player " << i << "'s turn." << endl;

        for (int j = 0; j < 4; j++) { // adding data 1-4
            cout << "Choose position A-H for D" << j << ":" endl;
            char pos;
            cin >> pos;
            while (pos < 'A' || pos > 'H') {
                cout << "Invalid position. Please enter a position between A and H." << endl;
                cin >> pos;
            }
            // first put in position A

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


