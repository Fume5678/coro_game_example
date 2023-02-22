#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics.hpp>
#include <memory>

#include "Game.h"
#include "Utilites.hpp"
#include "CellGenerator.h"

CellGenerator cell_generator() {
    for (;;) {
        std::shared_ptr<Cell> ptr_cell =
            std::make_shared<Cell>(Cell::CellType::grass);
        co_yield ptr_cell;
    }
}

int main() {

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                            "Coro game");

    Game game(window);
    game.run();

    return 0;
}