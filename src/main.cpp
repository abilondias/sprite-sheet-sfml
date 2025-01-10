#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Background.h"
#include "Camera.h"
#include "Enemy.h"
#include "Player.h"

int main() {
    // these values can be constexpr because there are no changes of the window size currently
    // manually scaling the window won't affect calculation because it will be calculated as if the window is 800x600
    // Note: distortions may happen while resizing the window
    constexpr float windowWidth = 800;
    constexpr float windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight)}),
                            "Sprite Sheet Render");
    window.setFramerateLimit(60);

    const std::string backgroundTexturePath = "assets/image/brawler/scenario.png";
    const std::string playerTexturePath = "assets/image/brawler/sheet.png";
    const std::string enemyTexturePath = "assets/image/brawler/enemy-sheet1.png";

    Game::Background background(backgroundTexturePath, window,
                                std::vector{
                                    Game::BoundsCheck(30, 315.f),
                                    Game::BoundsCheck(70, Game::InterpolationValues(30, 70, 315, 360)),
                                    Game::BoundsCheck(970, 360.f),
                                    Game::BoundsCheck(1225, 260.f),
                                    Game::BoundsCheck(1270, Game::InterpolationValues(1225, 1270, 260, 310)),
                                    Game::BoundsCheck(1520, 310.f),
                                    Game::BoundsCheck(std::numeric_limits<float>::max(), 260.f)
                                });

    Game::Player player(playerTexturePath, background.getScale());
    Game::Enemy enemy(enemyTexturePath, background.getScale(), player);
    Game::Camera camera(player, window, background.getWidth());

    sf::Clock clock;

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();
        while (const auto& e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();

        // update game objects
        player.update(delta);
        float playerX = std::clamp(player.getPosition().x, 0.f, background.getWidth());
        float playerY =
            std::clamp(player.getPosition().y, background.getVerticalBounds(player.getPosition().x), windowHeight);
        player.setPosition({playerX, playerY});

        enemy.update(delta);
        float enemyX = std::clamp(enemy.getPosition().x, 0.f, background.getWidth());
        float enemyY =
            std::clamp(enemy.getPosition().y, background.getVerticalBounds(enemy.getPosition().x), windowHeight);
        enemy.setPosition({enemyX, enemyY});

        camera.update(delta);

        // render
        window.draw(background);
        window.draw(player);
        window.draw(enemy);

        window.display();
    }

    return 0;
}
