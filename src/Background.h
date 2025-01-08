#ifndef SCENARIO_H
#define SCENARIO_H

#include <SFML/Graphics.hpp>

namespace Game {
    class Background : public sf::Drawable, public sf::Transformable {
    public:
        float scale;
        float width;

        Background(const std::string& texturePath, const sf::RenderWindow& window);

        void update(const float& delta);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::Texture texture;
        sf::Sprite sprite;
    };

} // namespace Game

#endif // SCENARIO_H
