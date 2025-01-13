#ifndef SCENARIO_H
#define SCENARIO_H

#include <SFML/Graphics.hpp>
#include <vector>

namespace Game {
    struct InterpolationValues {
        float t1, t2, s1, s2;
    };

    struct BoundsCheck {
        float x;
        std::variant<float, InterpolationValues> check;

        BoundsCheck(float X, std::variant<float, InterpolationValues> c) : x(X), check(c) {}
    };

    class Scenario : public sf::Drawable {
    public:
        Scenario(const std::string& texturePath, const sf::RenderWindow& window, const std::vector<BoundsCheck> bcs);

        void update(const float& delta);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        float getVerticalBounds(float x);

        float getScale() const;

        void setScale(float v);

        float getWidth() const;

        void setWidth(float v);

        float getHeight() const;

        void setHeight(float v);

    private:
        sf::Texture texture;
        sf::Sprite sprite;

        float scale;
        float width;
        float height;

        std::vector<BoundsCheck> boundsChecks;

        float interpolate(float x, float t1, float t2, float s1, float s2);
    };

} // namespace Game

#endif // SCENARIO_H
