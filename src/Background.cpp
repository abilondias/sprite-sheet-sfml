#include "Background.h"

Game::Background::Background(const std::string& texturePath, const sf::RenderWindow& window) :
    texture(texturePath), sprite(texture) {

    scale = static_cast<float>(window.getSize().y) / texture.getSize().y;
    sprite.setScale({scale, scale});

    width = sprite.getGlobalBounds().size.x;
}

void Game::Background::update(const float& delta) {
    // identify if its worth it to crop the texture to the current view
}

void Game::Background::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }
