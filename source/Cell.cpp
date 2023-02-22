#include "Cell.h"
#include <stdexcept>
#include "Utilites.hpp"

Cell::Cell(CellType type) {
    bool is_load = false;
    switch (type) {

        case CellType::sand: {
            is_load = texture.loadFromFile(RESOURCE_PATH + "sand.png");
            break;
        }
        case CellType::grass: {
            is_load = texture.loadFromFile(RESOURCE_PATH + "grass.png");
            break;
        }
        case CellType::water: {
            is_load = texture.loadFromFile(RESOURCE_PATH + "water.png");
            break;
        }
        case CellType::rock: {
            is_load = texture.loadFromFile(RESOURCE_PATH + "rock.png");
            break;
        }
    }

    if (!is_load) {
        throw std::runtime_error("[ERROR] Failed to load cell texture");
    }

    setTexture(texture);
}