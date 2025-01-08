#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <SFML/Graphics.hpp>

namespace Game {

    class Movement {
    public:
        static constexpr sf::Vector2f up = {0, -1};
        static constexpr sf::Vector2f down = {0, 1};
        static constexpr sf::Vector2f left = {-1, 0};
        static constexpr sf::Vector2f right = {1, 0};
    };

} // namespace Game

#endif // MOVEMENT_H
