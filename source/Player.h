#ifndef __PLAYER__H__
#define __PLAYER__H__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>

class Player : public sf::Sprite {
public:
    Player() = default;

    void init();

    void handleEvent(sf::Event&);

    int  playerX() const;
    void setPlayerX(int playerX);

    int  playerY() const;
    void setPlayerY(int playerY);

private:
    sf::Texture texture;

    int player_x;
    int player_y;
};

#endif //!__PLAYER__H__