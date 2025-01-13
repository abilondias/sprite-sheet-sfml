#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Scenario.h"

namespace Game {
    class Enemy : public sf::Drawable {
    public:
        enum Direction { Left, Right };
        enum Status { Idle = 0, WalkingUp = 1, Walking = 2 };

        Enemy(const std::string& texturePath, Scenario& s, Player& p);

        void update(const float& delta);

        sf::Vector2f getPosition() const;
        void setPosition(sf::Vector2f v);
        void updateAnimation();

        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::Sprite sprite;

    private:
        sf::Texture texture;
        sf::Vector2f position;

        Player& player;
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
        const float speed = 180;
    };
} // namespace Game

#endif // ENEMY_H
