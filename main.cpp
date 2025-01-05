#include <SFML/Graphics.hpp>

class Player {
public:
    // assets
    sf::Texture idleStrip;
    sf::Sprite sprite;

    // transforms
    enum Direction { Left, Right};
    Direction direction;

    enum Status {
        Idle = 0,
        WalkingUp = 1,
        Walking = 2
    };

    Status status;

    sf::Clock animationClock;
    int currentFrame;
    int msFrameDuration;

    const sf::Vector2i spriteSize{24, 32};

    sf::Vector2f position;

    Player() : idleStrip("../../assets/image/brawler/sheet.png"),
                sprite(idleStrip), position(400, 300) {
        currentFrame = 0;
        msFrameDuration = 300;
        direction = Right;

        sprite.setTextureRect(sf::IntRect({0, 0}, spriteSize));
        sprite.setOrigin({12, 16});
        sprite.setScale({2.5f, 2.5f});
    }

    void update(float delta) {
        status = Idle;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            direction = Left;
            sprite.setScale({-2.5f, 2.5f});
            position.x -= 2.f;
            status = Walking;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            direction = Right;
            sprite.setScale({2.5f, 2.5f});
            position.x += 2.f;
            status = Walking;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            position.y -= 1.2f;
            status = WalkingUp;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            position.y += 1.2f;
            status = Walking;
        }

        currentFrame = (currentFrame + 1) % 4;  // Cycle between 0, 1, 2, 3

        sprite.setPosition(position);

        if (animationClock.getElapsedTime().asMilliseconds() >= msFrameDuration) {
            animationClock.restart();

            // cycle between sprite segment frames
            currentFrame = (currentFrame + 1) % 4;

            // update the texture rectangle
            sprite.setTextureRect(sf::IntRect({currentFrame * 24, status * 32}, spriteSize));
        }
    }
};

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Sprite Render");
    window.setFramerateLimit(60);

    auto player = std::make_unique<Player>();

    sf::Clock clock;
    while (window.isOpen()) {
        float delta = clock.getElapsedTime().asSeconds();
        while (const auto& e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear(sf::Color::White);

        player->update(delta);
        window.draw(player->sprite);

        window.display();
    }

    return 0;
}
