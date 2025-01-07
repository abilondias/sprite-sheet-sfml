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
        Status status = Idle;

        // animation
        sf::Clock animationClock;
        int currentFrame;
        const int msFrameDuration = 250;
        const sf::Vector2i spriteSize{24, 32};
        const float spriteScale;

        const short animationFrameCount = 4; // all used animations have 4 frames

        const float speed = 80;

        Player(const float scale) :
            textureSheet("assets/image/brawler/sheet.png"), sprite(textureSheet), position(100, 500),
            spriteScale(scale) {
            currentFrame = 0;
            direction = Right;

            sprite.setTextureRect(sf::IntRect({0, 0}, spriteSize));
            sprite.setOrigin({spriteSize.x * 0.5f, spriteSize.y * 0.5f});

            sprite.setScale({spriteScale, spriteScale});
        }

        void update(const float delta) {
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
    constexpr float windowWidth = 800;
    constexpr float windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight)}),
                            "Sprite Sheet Render");
    window.setFramerateLimit(60);

    const sf::Texture scenarioTexture("assets/image/brawler/scenario.png");
    sf::Sprite scenario(scenarioTexture);
    const float scenarioScale = static_cast<float>(window.getSize().y) / scenarioTexture.getSize().y;
    scenario.setScale({scenarioScale, scenarioScale});

    const auto player = std::make_unique<Game::Player>(scenarioScale);

    const float scenarioWidth = scenario.getGlobalBounds().size.x;
    constexpr float halfWindowWidth = windowWidth * 0.5f;
    constexpr float halfWindowHeight = windowHeight * 0.5f;
    constexpr float minimumViewCenter = halfWindowWidth;
    const float maximumViewCenter = scenarioWidth - halfWindowWidth;

    sf::Clock clock;

    auto view = window.getView();

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        while (const auto& e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        window.clear();

        player->update(delta);

        // there's still free vertical movement
        player->position.x = std::clamp(player->position.x, 0.f, scenarioWidth);
        // TODO: use vertex array to create vertical bounds matching the scenario
        player->position.y = std::clamp(player->position.y, 0.f, windowHeight);

        // view handling based on the scenario size/image
        // points on the screen based on the current view position, where the view should start moving
        const float leftThreshold = view.getCenter().x - 0.4f * windowWidth;
        const float rightThreshold = view.getCenter().x + 0.4f * windowWidth;

        float viewCenterX = view.getCenter().x;
        // calculate new center if player moves past the thresholds
        if (player->position.x < leftThreshold) {
            viewCenterX = player->position.x + 0.4f * windowWidth;
            viewCenterX = std::clamp(viewCenterX, minimumViewCenter, maximumViewCenter);
        } else if (player->position.x > rightThreshold) {
            viewCenterX = player->position.x - 0.4f * windowWidth;
            viewCenterX = std::clamp(viewCenterX, minimumViewCenter, maximumViewCenter);
        }

        view.setCenter({viewCenterX, halfWindowHeight});
        window.setView(view);

        window.draw(scenario);
        window.draw(player->sprite);

        window.display();
    }

    return 0;
}
