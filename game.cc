#include <iostream>
#include <map>
#include "game.h"
#include "link.h"
#include "player.h"

using namespace std;

Game::Game(vector<Player*> players, Board* board):
    players(players), currplayer(0), board(board) {}

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

    players.resize(numPlayers);
    
    // Initialize each player
    for (int i = 0; i < numPlayers; i++) {
        players[i] = new Player(i);
        cout << "\nPlayer " << i + 1 << "'s turn to place links." << endl;
        
        // Track which positions are occupied
        vector<bool> occupied(8, false);
        
        // Place Data links (D1-D4)
        for (int j = 1; j <= 4; j++) {
            cout << "Choose position (a-h) for D" << j << ": ";
            char pos;
            cin >> pos;
            
            // Validate input
            while (pos < 'a' || pos > 'h' || occupied[pos - 'a']) {
                cout << "Invalid position. Please enter an unoccupied position (a-h): ";
                cin >> pos;
            }
            
            // Create and add Data link
            Link* newLink = new Link(pos, i, j, false, false, false, false);
            players[i]->addLink(newLink);
            occupied[pos - 'a'] = true;
        }
        
        // Place Virus links (V1-V4)
        for (int j = 1; j <= 4; j++) {
            cout << "Choose position (a-h) for V" << j << ": ";
            char pos;
            cin >> pos;
            
            // Validate input
            while (pos < 'a' || pos > 'h' || occupied[pos - 'a']) {
                cout << "Invalid position. Please enter an unoccupied position (a-h): ";
                cin >> pos;
            }
            
            // Create and add Virus link
            Link* newLink = new Link(pos, i, j, false, false, false, true);
            players[i]->addLink(newLink);
            occupied[pos - 'a'] = true;
        }
        
        initializePlayerAbilities(players[i]);
    }
    
    // Initialize board state
    board->initializeBoard(players);
    currplayer = 0;
}

void Game::processCommand(const string& cmd) {
    // Implementation here
}

bool Game::isGameOver() const {
    for (Player* player : players) {
        if (player->hasWon() || player->hasLost()) {
            return true;
        }
    }
    return false;
}

void Game::switchPlayer() {
    currplayer = (currplayer + 1) % players.size();
}

Ability* Game::createAbility(AbilityType type) {
    switch (type) {
        case AbilityType::LINK_BOOST: return new LinkBoost();
        case AbilityType::FIREWALL: return new Firewall();
        case AbilityType::DOWNLOAD: return new Download();
        case AbilityType::SCAN: return new Scan();
        case AbilityType::POLARIZE: return new Polarize();
        case AbilityType::JUST_SAY_NO: return new JustSayNo();
        case AbilityType::ROAD_WORK_AHEAD: return new RoadWorkAhead();
        case AbilityType::ROULETTE: return new Roulette();
        default: return nullptr;
    }
}

void Game::displayAbilityMenu() const {
    cout << "\nChoose abilities (max " << MAX_ABILITIES << " total, max " 
         << MAX_SAME_ABILITY << " of each type):\n";
    cout << "1. Link Boost\n2. Firewall\n3. Download\n4. Scan\n"
         << "5. Polarize\n6. Just Say No\n7. Road Work Ahead\n8. Roulette\n";
}

bool Game::isValidAbilityChoice(int choice) const {
    return choice >= 1 && choice <= 8;
}

void Game::initializePlayerAbilities(Player* player) {
    if (!player) return;
    
    map<string, int> abilityCount;
    int abilitiesChosen = 0;
    
    displayAbilityMenu();
    
    while (abilitiesChosen < MAX_ABILITIES) {
        cout << "\nChoose ability " << (abilitiesChosen + 1) 
             << " of " << MAX_ABILITIES << ": ";
        
        int choice;
        cin >> choice;
        
        if (!isValidAbilityChoice(choice)) {
            cout << "Invalid choice. Please select 1-8.\n";
            continue;
        }
        
        Ability* newAbility = nullptr;
        switch (choice) {
            case 1: newAbility = new LinkBoost(); break;
            case 2: newAbility = new Firewall(); break;
            case 3: newAbility = new Download(); break;
            case 4: newAbility = new Scan(); break;
            case 5: newAbility = new Polarize(); break;
            case 6: newAbility = new JustSayNo(); break;
            case 7: newAbility = new RoadWorkAhead(); break;
            case 8: newAbility = new Roulette(); break;
        }
        
        if (abilityCount[newAbility->getName()] >= MAX_SAME_ABILITY) {
            cout << "Maximum count (" << MAX_SAME_ABILITY 
                 << ") reached for " << newAbility->getName() << ". Choose another.\n";
            delete newAbility;
            continue;
        }
        
        player->addAbility(newAbility);
        abilityCount[newAbility->getName()]++;
        abilitiesChosen++;
    }
}
