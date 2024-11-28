#include "game.h"
#include <memory>
#include <vector>

int main() {
    std::vector<std::unique_ptr<Player>> players;
    Game game(std::move(players));
    game.run();
    return 0;
}