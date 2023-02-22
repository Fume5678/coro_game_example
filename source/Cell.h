#ifndef __CELL__H__
#define __CELL__H__

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Cell : public sf::Sprite {
public:
    enum class CellType { sand, grass, water, rock };
    Cell(CellType type);

private:
    sf::Texture texture;
};

#endif //!__CELL__H__