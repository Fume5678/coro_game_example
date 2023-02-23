#include "Game.h"

#include <SFML/Window/Event.hpp>
#include <coroutine>
#include <exception>
#include <memory>
#include <random>
#include <iostream>
#include <execution>
#include <algorithm>
#include <stdexcept>

#include "CellGenerator.h"
#include "Utilites.hpp"

Game::Game(sf::RenderWindow& window) : window{window}, cell_gen{nullptr} {
    should_stop = false;
}

CellGenerator Game::cell_generator() {
    std::random_device           rd;
    std::mt19937                 gen(rd());
    std::discrete_distribution<> d({70, 10, 10, 10});

    std::shared_ptr<Cell> ptr_cell = nullptr;
    while (true) {
        switch (d(gen)) {
            case 0: {
                ptr_cell = std::make_shared<Cell>(Cell::CellType::sand);
                break;
            }
            case 1: {
                ptr_cell = std::make_shared<Cell>(Cell::CellType::grass);
                break;
            }
            case 2: {
                ptr_cell = std::make_shared<Cell>(Cell::CellType::rock);
                break;
            }
            case 3: {
                ptr_cell = std::make_shared<Cell>(Cell::CellType::water);
                break;
            }
            default: {
                break;
            }
        }
        co_yield ptr_cell;
    }
}

void Game::init_map() {
    player.init();

    player.setPlayerY(rand() % MAP_SIZE);
    player.setPlayerX(rand() % MAP_SIZE);

    map.resize(MAP_SIZE * MAP_SIZE);
    std::fill(std::execution::par, map.begin(), map.end(), nullptr);

    std::cout << "[INFO] player pos: " << player.playerX() << " : "
              << player.playerY() << "\n";

    auto tmp           = cell_generator();
    cell_gen           = std::move(tmp);
    const int init_rad = 3;
    loadChunk({player.playerX(), player.playerY()}, init_rad);
}

void Game::run() {
    init_map();
    std::cout << "run\n";
    while (window.isOpen()) {
        handleEvent();
        draw();

        if (should_stop) {
            return;
        }
    }
}

void Game::handleEvent() {
    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            should_stop = true;
        }

        player.handleEvent(event);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
            loadChunk({player.playerX(), player.playerY()}, 3);
        }
    }
}

void Game::draw() {
    window.clear(sf::Color::Black);

    const int render_rad = 6;
    for (int i = 0; i < SCREEN_HEIGHT / CELL_SIZE; i++) {
        for (int j = 0; j < SCREEN_WIDTH / CELL_SIZE; j++) {
            if (i >= int(SCREEN_HEIGHT) / int(CELL_SIZE) / 2 - render_rad &&
                i <= int(SCREEN_HEIGHT) / int(CELL_SIZE) / 2 + render_rad &&
                j >= int(SCREEN_WIDTH) / int(CELL_SIZE) / 2 - render_rad &&
                j <= int(SCREEN_WIDTH) / int(CELL_SIZE) / 2 + render_rad) {

                int   off_x = -int(SCREEN_WIDTH) / int(CELL_SIZE) / 2 + j;
                int   off_y = -int(SCREEN_HEIGHT) / int(CELL_SIZE) / 2 + i;
                Point p(player.playerX() + off_x, player.playerY() + off_y);

                try {
                    if (isFilledCell(p)) {
                        auto cell = map[mapInd(p)];
                        int  tmp  = SCREEN_WIDTH / 64 / 2;
                        cell->setPosition(j * int(CELL_SIZE), i * int(CELL_SIZE)); // On screen coords
                        window.draw(*cell);
                    }
                } catch (std::out_of_range) {
                } catch (std::exception& e) {
                    std::cout << "[ERROR] " << e.what() << "\n";
                }
            }
        }
    }

    window.draw(player);
    window.display();
}

bool Game::isFilledCell(Point p) const {
    if (!inMapBound(p)) {
        throw std::out_of_range("Point out map bounds");
    }

    return bool(map[mapInd(p)]);
}

bool Game::inMapBound(Point p) const {
    return p.x >= 0 && p.x < MAP_SIZE && p.y >= 0 && p.y < MAP_SIZE;
}

size_t Game::mapInd(Point p) const {
    if (!inMapBound(p)) {
        throw std::out_of_range("Point out map bounds");
    }
    return p.y * MAP_SIZE + p.x;
}

void Game::loadChunk(Point center, int rad) {
    for (int y = std::max(center.y - rad, 0);
         y < std::min(center.y + rad, (int)MAP_SIZE);
         y++) {
        for (int x = std::max(center.x - rad, 0);
             x < std::min(center.x + rad, (int)MAP_SIZE);
             x++) {
            Point p(x, y);
            if (inMapBound(p) && !isFilledCell(p)) {
                map[mapInd(p)] = cell_gen.next_cell();
            }
        }
    }
}
