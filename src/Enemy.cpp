#include <SFML/Graphics.hpp>

#include "Enemy.h"

Game::Enemy::Enemy(const std::string& texturePath, Scenario& s, Player& p) :
    texture(texturePath), sprite(texture), position(400, 500), scenario(s), player(p) {
    currentFrame = 0;
    direction = Right;

    sprite.setTextureRect(sf::IntRect({0, 0}, spriteSize));
    sprite.setOrigin({spriteSize.x * 0.5f, spriteSize.y * 0.5f});
    sprite.setScale({spriteScale, spriteScale});
}

void Game::Enemy::update(const float& delta) {
    status = Idle;
    const auto distance = player.getPosition() - position;

    // TODO: limit axis movement when reaching thresholds
    if (std::abs(distance.x) < 50 && std::abs(distance.y) < 30) {
        status = Idle;
    } else {
        if (distance.x < 0) {
            direction = Left;
            sprite.setScale({-1 * spriteScale, spriteScale});
            status = Walking;
        } else {
            direction = Right;
            sprite.setScale({spriteScale, spriteScale});
            status = Walking;
        }

        position = position + distance.normalized() * delta * speed;

        if (distance.y < 0) {
            status = WalkingUp;
        }

        position.x = std::clamp(position.x, 0.f, scenario.getWidth());
        position.y = std::clamp(position.y, scenario.getVerticalBounds(position.x), scenario.getHeight());

        sprite.setPosition(position);
    }

    updateAnimation();
}

void Game::Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }

sf::Vector2f Game::Enemy::getPosition() const { return position; }

void Game::Enemy::setPosition(sf::Vector2f v) { position = v; }

void Game::Enemy::updateAnimation() {
    if (animationClock.getElapsedTime().asMilliseconds() >= msFrameDuration) {
        animationClock.restart();

        // cycle between sprite segment frames
        currentFrame = (currentFrame + 1) % animationFrameCount;

        // update the texture rectangle
        sprite.setTextureRect(sf::IntRect({currentFrame * 24, status * 32}, spriteSize));
    }
}
