#include <iostream>
#include <map>
#include <vector>
#include "game.h"
#include "link.h"
#include "player.h"
#include "board.h"
#include "ability.h"
#include "download.h"
#include "linkboost.h"
#include "firewall.h"
#include "scan.h"
#include "polarize.h"
#include "roadworkahead.h"
#include "roulette.h"
#include "bomb.h"
#include "graphicsobserver.h"
#include "textobserver.h"
#include <sstream>
#include <fstream>
#include <algorithm>
#include <utility>

Game::Game(vector<unique_ptr<Player>> players, bool graphics) : 
    players(std::move(players)), 
    currplayer(0), 
    board(make_unique<Board>())
{
    attach(make_unique<TextObserver>(this));
    if (graphics) {
        attach(make_unique<GraphicsObserver>(this));
    }
}

Game::~Game() {
    while (!observers.empty()) {
        detach(std::move(observers.back()));
    }
}

void Game::start() {
    cout << "How many players are playing, 2 or 4? ('quit' to exit): " << endl;
    std::string inputLine;
    int numPlayers = 0;

    while (numPlayers != 2 && numPlayers != 4) {
        cout << "Enter number of players: ";

        if (!std::getline(cin, inputLine)) {
            cout << "\nExiting." << endl;
            exit(0);
        }

        else if (inputLine == "quit") {
            cout << "Game has quit" << endl;
            exit(0);
        }

        try {
            numPlayers = std::stoi(inputLine);
        } catch (const std::invalid_argument&) {
            cout << "Invalid, enter a number (2 or 4) or 'quit'." << endl;
            continue;
        }

        if (numPlayers != 2 && numPlayers != 4) {
            cout << "Invalid number of players. Please enter 2 or 4." << endl;
        }
    }

    players.clear();

    // Initialize each player
    for (int i = 0; i < numPlayers; i++) {
        auto player = std::make_unique<Player>(i);
        cout << "\nPlayer " << i + 1 << "'s turn to place links." << endl;
        
        vector<bool> occupied = {false, false, false, false, false, false, false, false};
        
        // data
        for (int j = 1; j <= 4; j++) {
            i == 0 ? cout << "Choose position (a-h) for D" << j << ": " : cout << "Choose position (A-H) for D" << j << ": ";
            char pos;
            cin >> pos; 
            pos = tolower(pos); // convert to lower for same functionality
            
            while ((pos < 'a' || pos > 'h' || occupied[pos - 'a'])) {
                i == 0 ? cout << "Invalid position. Please enter an unoccupied position (a-h): " : cout << "Invalid position. Please enter an unoccupied position (A-H): ";
                cin >> pos;
                pos = tolower(pos);
            }
            
            auto newLink = std::make_unique<Link>(i == 1 ? toupper(pos) : pos, i, j, false, (i == 0) ? ((pos - 'a'== 3 || pos - 'a' == 4) ? 1 : 0) : ((pos - 'a' == 3 || pos - 'a' == 4) ? 6 : 7), pos - 'a');
            player->addLink(std::move(newLink));
            occupied[pos - 'a'] = true;
        }
        
        // virus
        for (int j = 1; j <= 4; j++) {
            i == 0 ? cout << "Choose position (a-h) for V" << j << ": " : cout << "Choose position (A-H) for V" << j << ": ";
            char pos;
            cin >> pos;
            pos = tolower(pos);
            
            while (pos < 'a' || pos > 'h' || occupied[pos - 'a']) {
                i == 0 ? cout << "Invalid position. Please enter an unoccupied position (a-h): " : cout << "Invalid position. Please enter an unoccupied position (A-H): ";
                cin >> pos;
                pos = tolower(pos);
            }
            
            auto newLink = std::make_unique<Link>(i == 1 ? toupper(pos) : pos, i, j, true, (i == 0) ? ((pos - 'a' == 3 || pos - 'a' == 4) ? 1 : 0) : ((pos - 'a' == 3 || pos - 'a' == 4) ? 6 : 7), pos - 'a');
            player->addLink(std::move(newLink));
            occupied[pos - 'a'] = true;
        }
        
        initializePlayerAbilities(player.get());
        players.push_back(std::move(player));
    }
    
    // After all players and abilities are initialized, initialize the board with players
    board->initializeBoard(players);
    
    currplayer = 0;
}

void Game::run() {
    start(); 
    
    std::string firstLine;
    std::getline(std::cin, firstLine); // weird buffer

    string command;
    cout << "\nWelcome to RAIInet!" << endl;
    notifyObservers(); // initial display of board
    
    while (!isGameOver()) {
        Player* currentPlayer = players[currplayer].get();
        cout << "\nPlayer " << currentPlayer->getId() + 1 << "'s turn: " << endl;
        cout << "Enter command (or 'help' for commands): ";
        
        if (!getline(cin, command) || cin.eof()) {
            break;
        }

        if (command == "quit") {
            cout << "Game ended by player." << endl;
            return;
        }
        
        if (command == "help") {
            cout << "\nAvailable commands:" << endl;
            cout << "board - Displays the game board" << endl;
            cout << "sequence <file> - Execute commands from a file" << endl;
            cout << "move <link> <direction> - Move a link (directions: up, down, left, right)" << endl;
            cout << "abilities - Display available abilities" << endl;
            cout << "ability <ID> [parameters] - Use an ability" << endl;
            cout << "quit - Exit the game" << endl;
            cout << "op - For debugging, display all game info" << endl;
            continue;
        }
        
        processCommand(command);
    }
    
    // Game over - announce winner
    for (const auto& player : players) {
        if (player->hasWon()) {
            cout << "\nPlayer " << player->getId() + 1 << " wins by downloading 4 data!" << endl;
        } else if (player->hasLost()) {
            cout << "\nPlayer " << player->getId() + 1 << " loses by downloading 4 viruses!" << endl;
        }
    }
}

void Game::processCommand(const std::string& cmd) {
    std::vector<std::string> tokens;
    std::stringstream ss(cmd);
    std::string token;
    while (ss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.empty()) { // handle empty
        return;
    }
    
    // convert to lowercase for conversion

    std::string command = toLower(tokens[0]);
    
    if (command == "move") {
        // move <link> <direction>
        if (tokens.size() != 3) {
            std::cout << "Invalid move command format. Usage: move <link> <direction>" << std::endl;
            return;
        }
        
        std::string linkStr = tokens[1];
        std::string directionStr = toLower(tokens[2]);
        
        // check if a-h or A-H, handles caps
        if (linkStr.length() != 1 || 
            !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
              (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
            std::cout << "Enter a valid link (a-h or A-H)." << std::endl;
            return;
        }
        
        char linkId = std::tolower(linkStr[0]);
        
        // Validate direction
        Direction dir;
        if (directionStr == "up") {
            dir = Direction::UP;
        } else if (directionStr == "down") {
            dir = Direction::DOWN;
        } else if (directionStr == "left") {
            dir = Direction::LEFT;
        } else if (directionStr == "right") {
            dir = Direction::RIGHT;
        } else {
            std::cout << "Invalid direction (up, down, left, right)." << std::endl;
            return;
        }
        
        // find the link in the current player's links
        Player* currentPlayer = players[currplayer].get();
        const auto& links = currentPlayer->getLinks();
        Link* targetLink = nullptr;
        
        // find the link we need to move
        for (const auto& linkPtr : links) {
            if (std::tolower(linkPtr->getId()) == linkId && !linkPtr->getDownloaded()) {
                targetLink = linkPtr.get();
                break;
            }
        }
        
        if (!targetLink) {
            std::cout << "Link '" << linkStr << "' not found." << std::endl;
            return;
        }
        
        // move the link, if successful
        if (board->moveLink(targetLink, dir)) {
            std::cout << "Moved link '" << linkStr << "' " << directionStr << "." << std::endl;
            currentPlayer->setUsedAbilityThisTurn(false);
            switchPlayer();
            notifyObservers();
        } else { // if move failed
            std::cout << "Failed to move link '" << linkStr << "' " << directionStr << "" << std::endl;
        }
        
    } else if (command == "abilities") { // abilities menu
        Player* currentPlayer = players[currplayer].get();
        const auto& abilities = currentPlayer->getAbilities();
        
        std::cout << currentPlayer->getName() << "'s abilities:" << std::endl;
        for (int i = 0; i < abilities.size(); i++) {
            std::cout << i + 1 << ". " << abilities[i]->getName()<< " - " << (abilities[i]->getUsed() ? "Used" : "Available") << std::endl;
        }
        
    } else if (command == "ability") {
        if (players[currplayer]->hasUsedAbilityThisTurn()) {
            std::cout << "You have already used an ability this turn." << std::endl;
            return;
        }
        
        // ability <ID> *params*
        if (tokens.size() != 2 && tokens.size() != 3 && tokens.size() != 4) {
            std::cout << "Invalid ability command format. Usage: ability <ID> [parameters]" << std::endl;
            return;
        }
        
        int abilityID;
        Player* currentPlayer = players[currplayer].get();
        try {
            abilityID = std::stoi(tokens[1]);
        } catch (const std::invalid_argument&) {
            std::cout << "Choose a number for ability ID (1-5)" << std::endl;
            return;
        }
        
        if (abilityID < 1 || abilityID > currentPlayer->getAbilities().size()) {
            std::cout << "ID out of range" << std::endl;
            return;
        }
        
        Ability* ability = currentPlayer->getAbilities()[abilityID - 1].get(); // get index of ID
        if (ability->getUsed()) {
            std::cout << "Ability '" << ability->getName() << "' has already been used" << std::endl;
            return;
        }
        
        if (ability->getName() == "Link Boost") {
            // ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Link Boost (use ability <ID> <link>)" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link (use a-h or A-H)" << std::endl;
                return;
            }
            
            int linkIndex = linkStr[0] - 'a'; // index of link

            Link* targetLink = players[currplayer]->getLinks()[linkIndex].get();
            Cell* targetCell = board->getCell(targetLink->getRow(), targetLink->getCol());
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Link Boost' used on link '" << linkStr << "'." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use 'Link Boost' on '" << linkStr << "'." << std::endl;
            }
        } else if (ability->getName() == "Firewall") {
            // ability <ID> <row> <col>
            if (tokens.size() != 4) {
                std::cout << "Invalid firewall usage (use ability <ID> <row> <col>)" << std::endl;
                return;
            }
            
            int row, col;
            try {
                row = std::stoi(tokens[2]);
                col = std::stoi(tokens[3]);
            } catch (const std::invalid_argument&) {
                std::cout << "row and col must be integers" << std::endl;
                return;
            }
            
            if (row < 0 || row >= board->getRows() || col < 0 || col >= board->getCols()) {
                std::cout << "row and col must be within bounds" << std::endl;
                return;
            }
            
            Cell* targetCell = board->getCell(row, col);
            if (targetCell->isFirewallOn1() || targetCell->isFirewallOn2() ||
                targetCell->getServerPort() || targetCell->getLink() != nullptr) {
                std::cout << "Firewalls cannot be placed in server ports or on links" << std::endl;
                return;
            }
            
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Firewall' used at (" << row << ", " << col << ")." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use ability 'Firewall' at (" << row << ", " << col << ")." << std::endl;
            }
            
        } else if (ability->getName() == "Download") {
            // ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of download (use ability <ID> <link>)" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link (use a-h or A-H)" << std::endl;
                return;
            }

            int linkIndex = linkStr[0] - 'a';
            Link* targetLink = players[1 - currplayer]->getLinks()[linkIndex].get();
            Cell* targetCell = board->getCell(targetLink->getRow(), targetLink->getCol());
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Download' used on link '" << linkStr << "'." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use ability 'Download' on link '" << linkStr << "'." << std::endl;
            }
            
        } else if (ability->getName() == "Scan") {
            // ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Scan (use ability <ID> <link>)" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link (use a-h or A-H)" << std::endl;
                return;
            }

            int linkIndex = linkStr[0] - 'a';
            Link* targetLink = players[1 - currplayer]->getLinks()[linkIndex].get();
            Cell* targetCell = board->getCell(targetLink->getRow(), targetLink->getCol());
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Scan' used on link '" << linkStr << "'." << std::endl;
                notifyObservers();
            } else {
                std::cout << "Link '" << linkStr << "' not found." << std::endl;
            }
        } else if (ability->getName() == "Polarize") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Polarize (use ability <ID> <link>)" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link (use a-h or A-H)" << std::endl;
                return;
            }

            int linkIndex = linkStr[0] - 'a';
            Link* targetLink = players[1 - currplayer]->getLinks()[linkIndex].get();
            Cell* targetCell = board->getCell(targetLink->getRow(), targetLink->getCol());
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Polarize' used on link '" << linkStr << "'." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use ability 'Polarize' on link '" << linkStr << "'." << std::endl;
            }

        } else if (ability->getName() == "Road Work Ahead") {
            // ability <ID> <row> <col>, marks X
            if (tokens.size() != 4) {
                std::cout << "Invalid usage of Road Work Ahead (use ability <ID> <row> <col>)" << std::endl;
                return;
            }
            
            int row, col;
            try {
                row = std::stoi(tokens[2]);
                col = std::stoi(tokens[3]);
            } catch (const std::invalid_argument&) {
                std::cout << "row and col must be integers" << std::endl;
                return;
            }
            
            // ensure within bounds
            if (row < 0 || row >= board->getRows() || col < 0 || col >= board->getCols()) {
                std::cout << "row and col must be within bounds" << std::endl;
                return;
            }
            
            Cell* targetCell = board->getCell(row, col);
            if (targetCell->isCellBlocked()) {
                std::cout << "Cell (" << row << ", " << col << ") is already blocked" << std::endl;
                return;
            }
            
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Road Work Ahead' blocked cell (" << row << ", " << col << ")." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use ability 'Road Work Ahead' at (" << row << ", " << col << ")." << std::endl;
            }
            
        } else if (ability->getName() == "Roulette") {
            // ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Roulette (use ability <ID> <link>)" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link (use a-h or A-H)" << std::endl;
                return;
            }
            
            int linkIndex = linkStr[0] - 'a';
            Link* targetLink = players[1 - currplayer]->getLinks()[linkIndex].get();
            Cell* targetCell = board->getCell(targetLink->getRow(), targetLink->getCol());
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Roulette' used on link '" << linkStr << "'." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use ability 'Roulette' on link '" << linkStr << "'." << std::endl;
            }
            
        } else if (ability->getName() == "Bomb") {
            // ability <ID> <row> <col>
            if (tokens.size() != 4) {
                std::cout << "Invalid usage of Bomb (use ability <ID> <row> <col>)" << std::endl;
                return;
            }
            
            int row, col;
            try {
                row = std::stoi(tokens[2]);
                col = std::stoi(tokens[3]);
            } catch (const std::invalid_argument&) {
                std::cout << "row and col must be integers" << std::endl;
                return;
            }
            
            if (row < 0 || row >= board->getRows() || col < 0 || col >= board->getCols()) {
                std::cout << "row and col must be within bounds" << std::endl;
                return;
            }
            
            Cell* targetCell = board->getCell(row, col);
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                std::cout << "Ability 'Bomb' used at (" << row << ", " << col << ")." << std::endl;
                currentPlayer->setUsedAbilityThisTurn(true);
                notifyObservers();
            } else {
                std::cout << "Failed to use ability 'Bomb' at (" << row << ", " << col << ")." << std::endl;
            }
            
            
        } else {
            std::cout << "Ability '" << ability->getName() << "' is not recognized." << std::endl;
        }
        
    } else if (command == "board") {
        board->display();
    } else if (command == "sequence") {
        // sequence <file>
        if (tokens.size() != 2) {
            std::cout << "Invalid sequence command (use sequence <file>)" << std::endl;
            return;
        }
        
        std::string filename = tokens[1];
        std::ifstream infile(filename);
        
        if (!infile.is_open()) {
            std::cout << "Cannot open file " << filename << std::endl;
            return;
        }
        
        std::string fileCommands;
        while (std::getline(infile, fileCommands)) {
            std::cout << "Running command: " << fileCommands << std::endl;
            processCommand(fileCommands);
            if (isGameOver()) {
                break;
            }
        }
        
        infile.close();
        
    } else if (command == "quit") {
        std::cout << "Game has quit" << std::endl;
        exit(0);

    } else if (command == "op") {
        const auto& allPlayerInfo = board->getPlayers();
        for (const auto& playerInfo : allPlayerInfo) {
            std::cout << "Player " << playerInfo->getId() + 1 << ": " << std::endl;
            
            // display Links
            for (const auto& linkPtr : playerInfo->getLinks()) {
                char linkId = linkPtr->getId();
                std::string type = linkPtr->getIsVirus() ? "V" : "D";
                int strength = linkPtr->getStrength();
                bool downloaded = linkPtr->getDownloaded();
                std::cout << "  Link: " << linkId << " " << type << " " << strength 
                          << " is downloaded: " << (downloaded ? "yes" : "no") << " is revealed: " 
                          << (linkPtr->isRevealed() ? "yes" : "no") << " is boosted: " 
                          << linkPtr->getBoosted() << std::endl;
            }
            
            // display Abilities
            const auto& abilities = playerInfo->getAbilities();
            std::cout << "  Abilities:" << std::endl;
            for (const auto& ability : abilities) {
                std::cout << "\t" << ability->getName() 
                          << " - " << (ability->getUsed() ? "Used" : "Available") << std::endl;
            }
            std::cout << std::endl;
        }

        // blocked cells
        std::cout << "Blocked Cells:" << std::endl;
        for (int i = 0; i < board->getRows(); ++i) {
            for (int j = 0; j < board->getCols(); ++j) {
                Cell* cell = board->getCell(i, j);
                if (cell->isCellBlocked()) {
                    std::cout << "(" << i << ", " << j << ") ";
                }
            }
        }
        std::cout << std::endl;

        // firewalled cells
        std::cout << "Firewalled Cells:" << std::endl;
        for (int i = 0; i < board->getRows(); ++i) {
            for (int j = 0; j < board->getCols(); ++j) {
                Cell* cell = board->getCell(i, j);
                if (cell->isFirewallOn1() || cell->isFirewallOn2()) {
                    std::cout << "(" << i << ", " << j << ") ";
                }
            }
        }
        std::cout << std::endl;
    } else if (command == "sequence") {
        if (tokens.size() != 2) {
            std::cout << "Invalid, use: sequence <file>" << std::endl;
            return;
        }

        std::string filename = tokens[1];
        std::ifstream infile(filename);
        std::string fileCommands;
        while (std::getline(infile, fileCommands)) {
            processCommand(fileCommands);
            if (isGameOver()) {
                break;
            }
        }
        infile.close();
    } else {
        std::cout << "Invalid command: " << tokens[0] << std::endl;
    }
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
    currplayer = currplayer == 0 ? 1 : 0;
    board->setCurrentPlayer(currplayer);
}

void Game::displayAbilityMenu() const {
    cout << "\nChoose abilities (max " << MAX_ABILITIES << " total, max " << MAX_SAME_ABILITY << " of each type):" << endl;
    cout << "1. Link Boost" << endl << "2. Firewall" << endl << "3. Download" << endl << "4. Polarize" << endl
         << "5. Scan" << endl << "6. Bomb" << endl << "7. Road Work Ahead" << endl << "8. Roulette" << endl;
}


void Game::initializePlayerAbilities(Player* player) {
    int abilitiesChosen = 0;
    // {ability name, count}
    std::map<std::string, int> abilityCount;
    
    while (abilitiesChosen < MAX_ABILITIES) {
        cout << "\nChoose ability " << abilitiesChosen + 1 << " for Player " << player->getId() + 1 << ":" << endl;
        cout << "1. Link Boost" << endl << "2. Firewall" << endl << "3. Download" << endl << "4. Polarize" << endl
             << "5. Scan" << endl << "6. Bomb" << endl << "7. Road Work Ahead" << endl << "8. Roulette" << endl;
        
        int choice;
        cin >> choice;
        
        if (!(choice <= 8 && choice >= 1)) {
            cout << "Invalid choice. Please select a number between 1 and 8." << endl;
            cin.clear();
            cin.ignore();
            continue;
        }
        
        std::unique_ptr<Ability> newAbility;
        string abilityName;
        
        switch (choice) {
            case 1:
                newAbility = std::make_unique<LinkBoost>(player);
                abilityName = "Link Boost";
                break;
            case 2:
                newAbility = std::make_unique<Firewall>(player);
                abilityName = "Firewall";
                break;
            case 3:
                newAbility = std::make_unique<Download>(player);
                abilityName = "Download";
                break;
            case 4:
                newAbility = std::make_unique<Polarize>(player);
                abilityName = "Polarize";
                break;
            case 5:
                newAbility = std::make_unique<Scan>(player);
                abilityName = "Scan";
                break;
            case 6:
                newAbility = std::make_unique<Bomb>(player, board.get());
                abilityName = "Bomb";
                break;
            case 7:
                newAbility = std::make_unique<RoadWorkAhead>(player);
                abilityName = "Road Work Ahead";
                break;
            case 8:
                newAbility = std::make_unique<Roulette>(player);
                abilityName = "Roulette";
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                continue;
        }
        
        if (abilityCount[abilityName] >= MAX_SAME_ABILITY) {
            cout << "Maximum count (" << MAX_SAME_ABILITY << ") for " << abilityName << ". Choose another ability" << endl;
            continue;
        }
        
        abilityCount[abilityName]++;
        player->addAbility(std::move(newAbility));
        abilitiesChosen++;
    }
}

// separate white spaces and tokenize
std::vector<std::string> Game::split(const std::string& str) const {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    
    while (iss >> std::ws && iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// convert string to lowercase by iterating
std::string Game::toLower(const std::string& str) const {
    std::string output = str;
    std::transform(output.begin(), output.end(), output.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return output;
}

int Game::getCurrPlayer() const {
    return currplayer;
}

Player* Game::getPlayer(int id) const {
    return players[id].get();
}

Board* Game::getBoard() const {
    return board.get();
}

void Game::notifyObservers() {
    for (auto& observer : observers) {
        observer->notify();
    }
}
