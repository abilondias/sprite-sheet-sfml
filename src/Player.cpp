#include <SFML/Graphics.hpp>

#include "Movement.h"
#include "Player.h"
#include "Scenario.h"

Game::Player::Player(const std::string& texturePath, Scenario& s) :
    texture(texturePath), sprite(texture), position(100, 500), scenario(s) {
    currentFrame = 0;
    direction = Right;

    sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(spriteSize)));
    sprite.setOrigin({spriteSize.x * 0.5f, spriteSize.y * 0.5f});
    sprite.setScale({spriteScale, spriteScale});
}

void Game::Player::update(const float& delta) {
    status = Idle;
    moveDirection.x = std::clamp(moveDirection.x, -1.f, 1.f);
    moveDirection.y = std::clamp(moveDirection.y, -1.f, 1.f);

    if (moveDirection.x != 0 || moveDirection.y != 0) {
        status = Walking;
        direction = (moveDirection.x > 0) ? Right : Left;

        if (moveDirection.y < 0) {
            status = WalkingUp;
        }
    }

    position += moveDirection * speed * delta;
    position.x = std::clamp(position.x, 0.f, scenario.getWidth());
    position.y = std::clamp(position.y, scenario.getVerticalBounds(position.x), scenario.getHeight());
    sprite.setPosition(position);

    if (direction == Left) {
        sprite.setScale({-1.f * scenario.getScale(), scenario.getScale()});
    } else {
        sprite.setScale({scenario.getScale(), scenario.getScale()});
    }

    updateAnimation();
}

void Game::Player::registerActions(InputHandler& inputHandler) {
    inputHandler.registerAction(InputHandler::Action::MoveLeftPress, [this]() {
        moveDirection += Movement::left;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveRightPress, [this]() {
        moveDirection += Movement::right;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveUpPress, [this]() {
        moveDirection += Movement::up;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveDownPress, [this]() {
        moveDirection += Movement::down;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveLeftRelease, [this]() {
        moveDirection -= Movement::left;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveRightRelease, [this]() {
        moveDirection -= Movement::right;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveUpRelease, [this]() {
        moveDirection -= Movement::up;
        //
    });

    inputHandler.registerAction(InputHandler::Action::MoveDownRelease, [this]() {
        moveDirection -= Movement::down;
        //
    });
}

sf::Vector2f Game::Player::getPosition() const { return position; }

void Game::Player::setPosition(sf::Vector2f v) { position = v; }

void Game::Player::draw(sf::RenderTarget& target, sf::RenderStates states) const { target.draw(sprite, states); }

void Game::Player::updateAnimation() {
    if (animationClock.getElapsedTime().asMilliseconds() >= msFrameDuration) {
        animationClock.restart();

        // cycle between sprite segment frames
        currentFrame = (currentFrame + 1) % animationFrameCount;

        // update the texture rectangle
        sprite.setTextureRect(sf::IntRect({currentFrame * 24, status * 32}, spriteSize));
    }
}
