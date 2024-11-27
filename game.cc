#include <iostream>
#include <map>
#include <vector>
#include "game.h"
#include "link.h"
#include "player.h"
#include "board.h"
#include "ability.h"

using namespace std;

Game::Game(vector<unique_ptr<Player>> players) : players(move(players)), currplayer(0) {
    // initialize empty board, each cell is null
    auto board = make_unique<Board>;
}

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
        auto player = make_unique<Player>(i);
        cout << "\nPlayer " << i + 1 << "'s turn to place links." << endl;
        
        // Track which positions are occupied
        vector<bool> occupied = {false, false, false, false, false, false, false, false};
        
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
            auto newLink = make_unique<Link>(pos, i, j, false);
            player->addLink(move(newLink));
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
            auto newLink = make_unique<Link>(pos, i, j, true);
            player->addLink(move(newLink));
            occupied[pos - 'a'] = true;
        }
        
        initializePlayerAbilities(player.get());
        players.push_back(move(player));
    }
    
    // Initialize board state
    board->initializeBoard(players);
    currplayer = 0;
}

void Game::run() {
    while (!isGameOver()) {
        auto& currentPlayer = players[currplayer];
        cout << "\nIt's Player " << currentPlayer->getName() << "'s turn." << endl;
        
        // Display current board state
        board->display(); // Assume you have a display method in Board
        
        // Prompt for command
        cout << "Enter command: ";
        std::string cmd;
        cin >> cmd;
        
        // Process the command
        processCommand(cmd);
        
        // Check for game over conditions inside processCommand or here
        if (isGameOver()) {
            break;
        }
        
        // Switch to the next player
        switchPlayer();
    }
    
    // Determine and announce the winner
    for (const auto& player : players) {
        if (player->hasWon()) {
            cout << "Player " << player->getName() << " has won the game!" << endl;
            return;
        }
        if (player->hasLost()) {
            cout << "Player " << player->getName() << " has lost the game!" << endl;
            return;
        }
    }
}

void Game::processCommand(const string& cmd) {
    // Implementation here
}

bool Game::isGameOver() const {
    for (const auto& player : players) {
        if (player->hasWon() || player->hasLost()) {
            return true;
        }
    }
    return false;
}

void Game::switchPlayer() {
    currplayer = (currplayer + 1) % players.size();
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
    
    std::map<std::string, int> abilityCount;
    int abilitiesChosen = 0;
    
    displayAbilityMenu();
    
    while (abilitiesChosen < MAX_ABILITIES) {
        std::cout << "\nChoose ability " << (abilitiesChosen + 1) << " of " << MAX_ABILITIES << ": ";
        
        int choice;
        std::cin >> choice;
        
        if (!isValidAbilityChoice(choice)) {
            std::cout << "Invalid choice. Please select 1-8.\n";
            continue;
        }
        
        std::unique_ptr<Ability> newAbility;
        
        switch (choice) {
            case 1:
                newAbility = std::make_unique<LinkBoost>(player->getId());
                break;
            case 2:
                newAbility = std::make_unique<Firewall>(player->getId());
                break;
            case 3:
                newAbility = std::make_unique<Download>(player->getId());
                break;
            case 4:
                newAbility = std::make_unique<Scan>(player->getId());
                break;
            case 5:
                newAbility = std::make_unique<Polarize>(player->getId());
                break;
            case 6:
                newAbility = std::make_unique<JustSayNo>(player->getId());
                break;
            case 7:
                newAbility = std::make_unique<RoadWorkAhead>(player->getId());
                break;
            case 8:
                newAbility = std::make_unique<Roulette>(player->getId());
                break;
            default:
                std::cout << "Invalid choice. Please select a valid ability.\n";
                continue;
        }
        
        if (!newAbility) {
            std::cout << "Failed to create the selected ability.\n";
            continue;
        }
        
        if (abilityCount[newAbility->getName()] >= MAX_SAME_ABILITY) {
            std::cout << "Maximum count (" << MAX_SAME_ABILITY 
                      << ") reached for " << newAbility->getName() << ". Choose another.\n";
            continue;
        }
        
        player->addAbility(std::move(newAbility));
        abilityCount[player->getAbilities().back()->getName()]++;
        abilitiesChosen++;
    }
}
