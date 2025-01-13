#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

#include "InputHandler.h"
#include "Scenario.h"

namespace Game {
    class Player : public sf::Drawable {
    public:
        enum Direction { Left, Right };
        enum Status { Idle = 0, WalkingUp = 1, Walking = 2 };

        Player(const std::string& texturePath, Scenario& s);

        void update(const float& delta);

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void updateAnimation();

        void registerActions(InputHandler& inputHandler);

        sf::Vector2f getPosition() const;

        void setPosition(sf::Vector2f v);

    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::Vector2f moveDirection = {0, 0};
        Scenario& scenario;

        Direction direction;
        Status status = Idle;

        // animation
        sf::Clock animationClock;
        int currentFrame;
        const int msFrameDuration = 300;
        const sf::Vector2i spriteSize{24, 32};
        const float spriteScale = scenario.getScale();

        // all used animations have 4 frames
        const short animationFrameCount = 4;
        const float speed = 250;
    };
} // namespace Game

#endif // PLAYER_H
