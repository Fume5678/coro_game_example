#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <vector>
#include <memory>

#include "CellGenerator.h"
#include "Player.h"
#include "Cell.h"
#include "Utilites.hpp"

class Game {
public:
    Game(sf::RenderWindow& window);

    ~Game() {
        window.close();
    }

    // Change on my coroutine
    static CellGenerator cell_generator();

    void init_map();
    void run();
    void handleEvent();
    void draw();
    void loadChunk(Point center, int rad);

    bool   isFilledCell(Point p) const;
    bool   inMapBound(Point p) const;

    size_t mapInd(Point p) const;

private:
    bool                               should_stop;
    sf::RenderWindow&                  window;
    Player                             player;
    std::vector<std::shared_ptr<Cell>> map;
    CellGenerator                      cell_gen;
};

#endif // GAME_H
