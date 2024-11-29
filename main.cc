#include "game.h"
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    // Create players
    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::make_unique<Player>(0));
    players.push_back(std::make_unique<Player>(1));

    Game game{std::move(players)};

    if (argc == 2) {
        // Read from file
        std::ifstream inFile(argv[1]);
        if (!inFile) {
            std::cerr << "Error: Could not open file " << argv[1] << std::endl;
            return 1;
        }
        
        std::string line;
        while (std::getline(inFile, line)) {
            game.processCommand(line);
        }
    }

    game.run();  // Continue with interactive mode after file commands are processed
    return 0;
}
