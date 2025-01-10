#include "Background.h"

Game::Background::Background(const std::string& texturePath, const sf::RenderWindow& window,
                             std::vector<BoundsCheck> bcs) :
    texture(texturePath), sprite(texture), boundsChecks(std::move(bcs)) {

    scale = static_cast<float>(window.getSize().y) / texture.getSize().y;
    sprite.setScale({scale, scale});

    width = sprite.getGlobalBounds().size.x;
}

void Game::Background::update(const float& delta) {
    // identify if its worth it to crop the texture to the current view
}

float Game::Background::getScale() const { return scale; }

void Game::Background::setScale(float v) { scale = v; }

float Game::Background::getWidth() const { return width; }

void Game::Background::setWidth(float v) { width = v; }

void Game::Background::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }

float Game::Background::interpolate(float x, float t1, float t2, float s1, float s2) const {
    assert(t1 < t2);
    const float f = (x - t1) / (t2 - t1);
    const float g = f * (s2 - s1) + s1;
    return g;
}

// values need to be scaled based on window/texture size
float Game::Background::getVerticalBounds(float x) {
    for (auto& b : boundsChecks) {
        if (std::holds_alternative<float>(b.check) && x <= b.x) {
            return std::get<float>(b.check);
        }

        if (std::holds_alternative<InterpolationValues>(b.check) && x <= b.x) {
            const auto [t1, t2, s1, s2] = std::get<InterpolationValues>(b.check);
            return interpolate(x, t1, t2, s1, s2);
        }
    }

    return 0.f;
}
