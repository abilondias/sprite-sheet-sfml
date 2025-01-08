#include <SFML/Graphics.hpp>

#include "Movement.h"
#include "Player.h"

Game::Player::Player(const std::string& texturePath, const float& scale) :
    texture(texturePath), sprite(texture), position(100, 500), spriteScale(scale) {
    currentFrame = 0;
    direction = Right;

    sprite.setTextureRect(sf::IntRect({0, 0}, spriteSize));
    sprite.setOrigin({spriteSize.x * 0.5f, spriteSize.y * 0.5f});
    sprite.setScale({spriteScale, spriteScale});
}

void Game::Player::update(const float& delta) {
    status = Idle;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        direction = Left;
        sprite.setScale({-1 * spriteScale, spriteScale});
        position += Movement::left * speed * delta;
        status = Walking;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        direction = Right;
        sprite.setScale({spriteScale, spriteScale});
        position += Movement::right * speed * delta;
        status = Walking;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        position += Movement::up * speed * delta;
        status = WalkingUp;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        position += Movement::down * speed * delta;
        status = Walking;
    }

    sprite.setPosition(position);

    if (animationClock.getElapsedTime().asMilliseconds() >= msFrameDuration) {
        animationClock.restart();

        // cycle between sprite segment frames
        currentFrame = (currentFrame + 1) % animationFrameCount;

        // update the texture rectangle
        sprite.setTextureRect(sf::IntRect({currentFrame * 24, status * 32}, spriteSize));
    }
}

void Game::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }

sf::Vector2f Game::Player::getPosition() const { return position; }

void Game::Player::setPosition(sf::Vector2f v) { position = v; }
