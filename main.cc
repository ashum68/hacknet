#include "game.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    // Create vector to store players
    vector<unique_ptr<Player>> players;
    
    // Create players (for a 2-player game)
    players.push_back(make_unique<Player>(0));  // Player 1
    players.push_back(make_unique<Player>(1));  // Player 2
    
    // Create and start the game
    Game game(move(players));
    
    try {
        game.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 