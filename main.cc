#include "game.h"
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {
    bool graphics_enabled = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-graphics") {
            graphics_enabled = true;
        }
        else {
            std::cerr << "invalid" << std::endl;
            return 1;
        }
    }

    std::vector<std::unique_ptr<Player>> players;
    players.push_back(std::make_unique<Player>(0));
    players.push_back(std::make_unique<Player>(1));

    Game game{std::move(players), graphics_enabled};

    game.run();
    return 0;
}
