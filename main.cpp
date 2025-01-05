#include <SFML/Graphics.hpp>

class Player {
public:
    // assets
    sf::Texture idleStrip;
    sf::Sprite sprite;

    // transforms
    enum Direction { Left, Right};
    Direction direction;

    sf::Vector2f position;

    Player() : idleStrip("../../assets/image/brawler/idle.png"), sprite(idleStrip), position(400, 300) {
        direction = Right;

        sprite.setTextureRect(sf::IntRect({0, 0}, {24, 32}));
        sprite.setOrigin({12, 16});
        sprite.setScale({2.5f, 2.5f});
    }

    void update(float delta) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            position.y -= 2.f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            position.y += 2.f;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            direction = Left;
            sprite.setScale({-2.5f, 2.5f});
            position.x -= 2.f;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            direction = Right;
            sprite.setScale({2.5f, 2.5f});;
            position.x += 2.f;
        }

        sprite.setPosition(position);
    }
};

int main() {
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({800u, 600u}), "Sprite Render");
    window.setFramerateLimit(60);

    sf::CircleShape shape(10.f, 20.f);
    shape.setPosition(sf::Vector2f(400.f, 300.f));
    shape.setFillColor(sf::Color::Green);

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
