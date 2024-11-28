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
#include "justsayno.h"
#include "roadworkahead.h"
#include "roulette.h"
#include "graphicsobserver.h"
#include "textobserver.h"
#include <sstream>
#include <fstream>
#include <algorithm>

using namespace std;

Game::Game(vector<unique_ptr<Player>> players) : players(move(players)), currplayer(0), board(make_unique<Board>()) {
    // Initialize the board with players
    board->initializeBoard(this->players);
    
    // Create only text observer
    auto textObserver = make_unique<TextObserver>(board.get());
    
    // Attach observer to the board
    board->attach(textObserver.get());
    
    // Store observer
    this->observers.push_back(move(textObserver));
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
    start();  // Initialize the game and players
    
    string command;
    cout << "\nWelcome to RAIInet!" << endl;
    
    while (!isGameOver()) {
        Player* currentPlayer = players[currplayer].get();
        cout << "\nPlayer " << currentPlayer->getId() + 1 << "'s turn" << endl;
        cout << "Enter command (or 'help' for commands): ";
        
        getline(cin, command);
        
        if (command == "help") {
            cout << "\nAvailable commands:" << endl;
            cout << "move <link> <direction> - Move a link (directions: up, down, left, right)" << endl;
            cout << "abilities - Display available abilities" << endl;
            cout << "ability <ID> [parameters] - Use an ability" << endl;
            cout << "board - Display the game board" << endl;
            cout << "quit - Exit the game" << endl;
            continue;
        }
        
        processCommand(command);
        
        // Switch to next player after a valid move
        if (command.substr(0, 4) == "move") {
            switchPlayer();
        }
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
    // Tokenize the input command
    std::vector<std::string> tokens = split(cmd);
    
    if (tokens.empty()) {
        std::cout << "No command entered. Please try again." << std::endl;
        return;
    }
    
    // Convert command to lowercase for case-insensitive comparison
    std::string command = toLower(tokens[0]);
    
    if (command == "move") {
        // Command format: move <link> <direction>
        if (tokens.size() != 3) {
            std::cout << "Invalid move command format. Usage: move <link> <direction>" << std::endl;
            return;
        }
        
        std::string linkStr = tokens[1];
        std::string directionStr = toLower(tokens[2]);
        
        // Validate link identifier (e.g., a-h or A-H)
        if (linkStr.length() != 1 || 
            !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
              (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
            std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
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
            std::cout << "Invalid direction. Must be one of: up, down, left, right." << std::endl;
            return;
        }
        
        // Find the link in the current player's links
        Player* currentPlayer = players[currplayer].get();
        const auto& links = currentPlayer->getLinks();
        Link* targetLink = nullptr;
        
        for (const auto& linkPtr : links) {
            if (std::tolower(linkPtr->getId()) == linkId && !linkPtr->getDownloaded()) {
                targetLink = linkPtr.get();
                break;
            }
        }
        
        if (!targetLink) {
            std::cout << "Link '" << linkStr << "' not found or already downloaded." << std::endl;
            return;
        }
        
        // Attempt to move the link
        if (board->moveLink(targetLink, dir)) {
            std::cout << "Moved link '" << linkStr << "' " << directionStr << "." << std::endl;
        } else {
            std::cout << "Failed to move link '" << linkStr << "' " << directionStr << "." << std::endl;
        }
        
    } else if (command == "abilities") {
        // Display the current player's abilities
        Player* currentPlayer = players[currplayer].get();
        const auto& abilities = currentPlayer->getAbilities();
        
        std::cout << "Abilities for " << currentPlayer->getName() << ":" << std::endl;
        for (size_t i = 0; i < abilities.size(); ++i) {
            std::cout << i + 1 << ". " << abilities[i]->getName()
                      << " - " << (abilities[i]->getUsed() ? "Used" : "Available") << std::endl;
        }
        
    } else if (command == "ability") {
        // Command format: ability <ID> [additional parameters]
        if (tokens.size() < 2) {
            std::cout << "Invalid ability command format. Usage: ability <ID> [parameters]" << std::endl;
            return;
        }
        
        int abilityID;
        try {
            abilityID = std::stoi(tokens[1]);
        } catch (const std::invalid_argument&) {
            std::cout << "Invalid ability ID. Must be a number." << std::endl;
            return;
        }
        
        Player* currentPlayer = players[currplayer].get();
        if (abilityID < 1 || abilityID > currentPlayer->getAbilities().size()) {
            std::cout << "Ability ID out of range. Please select a valid ability ID." << std::endl;
            return;
        }
        
        Ability* ability = currentPlayer->getAbilities()[abilityID - 1].get();
        if (ability->getUsed()) {
            std::cout << "Ability '" << ability->getName() << "' has already been used." << std::endl;
            return;
        }
        
        // Handle specific abilities that require additional parameters
        if (ability->getName() == "Link Boost") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Link Boost. Usage: ability <ID> <link>" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
                return;
            }
            
            char linkId = std::tolower(linkStr[0]);
            const auto& links = currentPlayer->getLinks();
            Link* targetLink = nullptr;
            
            for (const auto& linkPtr : links) {
                if (std::tolower(linkPtr->getId()) == linkId && !linkPtr->getDownloaded()) {
                    targetLink = linkPtr.get();
                    break;
                }
            }
            
            if (!targetLink) {
                std::cout << "Link '" << linkStr << "' not found or already downloaded." << std::endl;
                return;
            }
            
            if (currentPlayer->useAbility(abilityID - 1, nullptr)) { // Assuming LinkBoost requires different handling
                // Apply Link Boost effect here
                // For example:
                // targetLink->enableBoost();
                std::cout << "Ability 'Link Boost' used on link '" << linkStr << "'." << std::endl;
            } else {
                std::cout << "Failed to use ability 'Link Boost' on link '" << linkStr << "'." << std::endl;
            }
            
        } else if (ability->getName() == "Firewall") {
            // Usage: ability <ID> <row> <col>
            if (tokens.size() != 4) {
                std::cout << "Invalid usage of Firewall. Usage: ability <ID> <row> <col>" << std::endl;
                return;
            }
            
            int row, col;
            try {
                row = std::stoi(tokens[2]);
                col = std::stoi(tokens[3]);
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid row or column. Must be integers." << std::endl;
                return;
            }
            
            // Validate board coordinates
            if (row < 0 || row >= board->getRows() || col < 0 || col >= board->getCols()) {
                std::cout << "Row or column out of bounds." << std::endl;
                return;
            }
            
            // Prevent placing firewall on server ports or occupied cells
            Cell* targetCell = board->getCell(row, col);
            if (targetCell->isFirewallOn1() || targetCell->isFirewallOn2() ||
                targetCell->getHasServerPort() || targetCell->getLink() != nullptr) {
                std::cout << "Cannot place Firewall on the specified cell." << std::endl;
                return;
            }
            
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                ability->use(targetCell);
                std::cout << "Ability 'Firewall' used at (" << row << ", " << col << ")." << std::endl;
            } else {
                std::cout << "Failed to use ability 'Firewall' at (" << row << ", " << col << ")." << std::endl;
            }
            
        } else if (ability->getName() == "Download") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Download. Usage: ability <ID> <link>" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
                return;
            }
            
            char linkId = std::tolower(linkStr[0]);
            // Find the opponent's link corresponding to linkId
            // Implementation depends on how links are identified across players
            // Example:
            // Link* targetLink = findOpponentLink(linkId);
            // if (targetLink) {
            //     ability->use(targetLink);
            //     std::cout << "Ability 'Download' used on link '" << linkStr << "'." << std::endl;
            // } else {
            //     std::cout << "Opponent's link '" << linkStr << "' not found." << std::endl;
            // }
            
            std::cout << "Ability 'Download' is not yet implemented." << std::endl;
            
        } else if (ability->getName() == "Scan") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Scan. Usage: ability <ID> <link>" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
                return;
            }
            
            char linkId = std::tolower(linkStr[0]);
            // Find the link to scan (can be own or opponent's, based on game rules)
            // Example:
            // Link* targetLink = findLink(linkId);
            // if (targetLink) {
            //     ability->use(targetLink);
            //     std::cout << "Ability 'Scan' used on link '" << linkStr << "'." << std::endl;
            // } else {
            //     std::cout << "Link '" << linkStr << "' not found." << std::endl;
            // }
            
            std::cout << "Ability 'Scan' is not yet implemented." << std::endl;
            
        } else if (ability->getName() == "Polarize") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Polarize. Usage: ability <ID> <link>" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
                return;
            }
            
            char linkId = std::tolower(linkStr[0]);
            // Find the link to polarize (could be opponent's link based on game rules)
            // Example:
            // Link* targetLink = findLink(linkId);
            // if (targetLink) {
            //     ability->use(targetLink);
            //     std::cout << "Ability 'Polarize' used on link '" << linkStr << "'." << std::endl;
            // } else {
            //     std::cout << "Link '" << linkStr << "' not found." << std::endl;
            // }
            
            std::cout << "Ability 'Polarize' is not yet implemented." << std::endl;
            
        } else if (ability->getName() == "Just Say No") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Just Say No. Usage: ability <ID> <link>" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
                return;
            }
            
            char linkId = std::tolower(linkStr[0]);
            // Implement Just Say No logic
            std::cout << "Ability 'Just Say No' is not yet implemented." << std::endl;
            
        } else if (ability->getName() == "Road Work Ahead") {
            // Usage: ability <ID> <row> <col>
            if (tokens.size() != 4) {
                std::cout << "Invalid usage of Road Work Ahead. Usage: ability <ID> <row> <col>" << std::endl;
                return;
            }
            
            int row, col;
            try {
                row = std::stoi(tokens[2]);
                col = std::stoi(tokens[3]);
            } catch (const std::invalid_argument&) {
                std::cout << "Invalid row or column. Must be integers." << std::endl;
                return;
            }
            
            // Validate board coordinates
            if (row < 0 || row >= board->getRows() || col < 0 || col >= board->getCols()) {
                std::cout << "Row or column out of bounds." << std::endl;
                return;
            }
            
            Cell* targetCell = board->getCell(row, col);
            if (targetCell->isCellBlocked()) {
                std::cout << "Cell (" << row << ", " << col << ") is already blocked." << std::endl;
                return;
            }
            
            if (currentPlayer->useAbility(abilityID - 1, targetCell)) {
                ability->use(targetCell);
                std::cout << "Ability 'Road Work Ahead' used at (" << row << ", " << col << ")." << std::endl;
            } else {
                std::cout << "Failed to use ability 'Road Work Ahead' at (" << row << ", " << col << ")." << std::endl;
            }
            
        } else if (ability->getName() == "Roulette") {
            // Usage: ability <ID> <link>
            if (tokens.size() != 3) {
                std::cout << "Invalid usage of Roulette. Usage: ability <ID> <link>" << std::endl;
                return;
            }
            
            std::string linkStr = tokens[2];
            if (linkStr.length() != 1 || 
                !((linkStr[0] >= 'a' && linkStr[0] <= 'h') || 
                  (linkStr[0] >= 'A' && linkStr[0] <= 'H'))) {
                std::cout << "Invalid link identifier. Must be a single letter (a-h or A-H)." << std::endl;
                return;
            }
            
            char linkId = std::tolower(linkStr[0]);
            // Implement Roulette logic
            std::cout << "Ability 'Roulette' is not yet implemented." << std::endl;
            
        } else {
            std::cout << "Ability '" << ability->getName() << "' is not recognized." << std::endl;
        }
        
    } else if (command == "board") {
        // Display the current state of the board
        board->display(); // Assuming Board::display() handles POV
        
    } else if (command == "sequence") {
        // Command format: sequence <file>
        if (tokens.size() != 2) {
            std::cout << "Invalid sequence command format. Usage: sequence <file>" << std::endl;
            return;
        }
        
        std::string filename = tokens[1];
        std::ifstream infile(filename);
        
        if (!infile.is_open()) {
            std::cout << "Failed to open sequence file: " << filename << std::endl;
            return;
        }
        
        std::string fileCmd;
        while (std::getline(infile, fileCmd)) {
            std::cout << "Executing command: " << fileCmd << std::endl;
            processCommand(fileCmd);
            if (isGameOver()) {
                break;
            }
        }
        
        infile.close();
        
    } else if (command == "quit" || command == "exit") {
        // Exit the game
        std::cout << "Exiting the game. Goodbye!" << std::endl;
        exit(0);
        
    } else {
        std::cout << "Unknown command: " << tokens[0] << ". Please try again." << std::endl;
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

// Helper function to split a string into tokens based on whitespace
std::vector<std::string> Game::split(const std::string& str) const {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Helper function to convert a string to lowercase
std::string Game::toLower(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return lowerStr;
}

int Game::getCurrPlayer() const {
    return currplayer;
}

unique_ptr<Player> Game::getPlayer(int id) const {
    return players[id];
}

unique_ptr<Board> Game::getBoard() const {
    return board;
}