#include <SFML/Graphics.hpp>
#include <cmath>

namespace Game {
    class Movement {
    public:
        static constexpr sf::Vector2f up = {0, -1};
        static constexpr sf::Vector2f down = {0, 1};
        static constexpr sf::Vector2f left = {-1, 0};
        static constexpr sf::Vector2f right = {1, 0};
    };

    class Player {
    public:
        sf::Texture textureSheet;
        sf::Sprite sprite;

        sf::Vector2f position;

        enum Direction { Left, Right };
        Direction direction;

        enum Status { Idle = 0, WalkingUp = 1, Walking = 2 };
        Status status;

        // animation
        sf::Clock animationClock;
        int currentFrame;
        const int msFrameDuration = 250;
        const sf::Vector2i spriteSize{24, 32};
        const float spriteScale;

        const short animationFrameCount = 4; // all used animations have 4 frames

        const float speed = 80;

        Player(const float scale) :
            textureSheet("../../assets/image/brawler/sheet.png"), sprite(textureSheet), position(100, 500),
            spriteScale(scale) {
            currentFrame = 0;
            direction = Right;

            sprite.setTextureRect(sf::IntRect({0, 0}, spriteSize));
            sprite.setOrigin({12, 16});

            sprite.setScale({spriteScale, spriteScale});
        }

        void update(float delta) {
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
    };
}; // namespace Game

int main() {
    constexpr unsigned windowWidth = 800;
    constexpr unsigned windowHeight = 600;

    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({windowWidth, windowHeight}), "Sprite Sheet Render");
    window.setFramerateLimit(60);

    const sf::Texture scenarioTexture("../../assets/image/brawler/scenario.png");
    sf::Sprite scenario(scenarioTexture);

    const float scenarioScale = static_cast<float>(window.getSize().y) / scenarioTexture.getSize().y;
    scenario.setScale({scenarioScale, scenarioScale});

    const auto player = std::make_unique<Game::Player>(scenarioScale);

    const float windowTextureWidth = window.getSize().x / scenarioScale;
    sf::IntRect textureRect = {{0, 0}, {int(windowTextureWidth), int(scenarioTexture.getSize().y)}};

    sf::Clock clock;

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        while (const auto& e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();

        player->update(delta);

        // simple background and bounds handling by moving the texture rectangle based on the % of the screen
        // there's still free vertical movement
        if (player->position.x < 0) {
            player->position.x = 0;
        } else if (player->position.x > window.getSize().x) {
            player->position.x = windowWidth;
        }

        // ex.: player's x at 400 is 50%, so move half of it's possible distance without going out of the image bounds
        const float backgroundPercent = player->position.x / windowWidth;
        textureRect.position.x = backgroundPercent * (scenarioTexture.getSize().x - windowTextureWidth);
        scenario.setTextureRect(textureRect);

        window.draw(scenario);
        window.draw(player->sprite);

        window.display();
    }

    return 0;
}
