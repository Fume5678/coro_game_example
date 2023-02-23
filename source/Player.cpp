#include "Player.h"

#include "Utilites.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

void Player::init() {
    if (!texture.loadFromFile(RESOURCE_PATH + "player.png")) {
        throw std::runtime_error("Failed load player texture\n");
    }
    setTexture(texture);

    setPosition(SCREEN_WIDTH / CELL_SIZE / 2 * float(CELL_SIZE) + 10,
                SCREEN_HEIGHT / CELL_SIZE / 2 * float(CELL_SIZE) - 10);
}

void Player::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            player_x--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            player_x++;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            player_y--;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            player_y++;
        }
        std::cout << "[INFO] player pos: " << player_x << " : " << player_y
                  << "\n";
    }
}

int Player::playerX() const {
    return player_x;
}

void Player::setPlayerX(int playerX) {
    player_x = playerX;
}

int Player::playerY() const {
    return player_y;
}

void Player::setPlayerY(int playerY) {
    player_y = playerY;
}