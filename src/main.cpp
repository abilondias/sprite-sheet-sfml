#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Camera.h"
#include "Enemy.h"
#include "EventHandler.h"
#include "Player.h"
#include "Scenario.h"

int main() {
    // these values can be constexpr because there are no changes of the window size currently
    // manually scaling the window won't affect calculation because it will be calculated as if the window is 800x600
    // Note: distortions may happen while resizing the window
    constexpr float windowWidth = 800;
    constexpr float windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode({static_cast<unsigned>(windowWidth), static_cast<unsigned>(windowHeight)}),
                            "Sprite Sheet Render");

    Game::InputHandler inputs{};
    Game::EventHandler events(window, inputs);

    window.setFramerateLimit(60);

    const std::string backgroundTexturePath = "assets/image/brawler/scenario.png";
    const std::string playerTexturePath = "assets/image/brawler/sheet.png";
    const std::string enemyTexturePath = "assets/image/brawler/enemy-sheet1.png";


    Game::Scenario scenario(backgroundTexturePath, window,
                                std::vector{
                                    Game::BoundsCheck(30, 315.f),
                                    Game::BoundsCheck(70, Game::InterpolationValues(30, 70, 315, 360)),
                                    Game::BoundsCheck(970, 360.f),
                                    Game::BoundsCheck(1225, 260.f),
                                    Game::BoundsCheck(1270, Game::InterpolationValues(1225, 1270, 260, 310)),
                                    Game::BoundsCheck(1520, 310.f),
                                    Game::BoundsCheck(std::numeric_limits<float>::max(), 260.f)
                                });

    Game::Player player(playerTexturePath, scenario.getScale());
    Game::Enemy enemy(enemyTexturePath, scenario.getScale(), player);
    Game::Camera camera(player, window, scenario.getWidth());

    sf::Clock clock;

    while (window.isOpen()) {
        float delta = clock.restart().asSeconds();

        events.poll();

        window.clear();

        // update game objects
        player.update(delta);
        float playerX = std::clamp(player.getPosition().x, 0.f, scenario.getWidth());
        float playerY =
            std::clamp(player.getPosition().y, scenario.getVerticalBounds(player.getPosition().x), windowHeight);
        player.setPosition({playerX, playerY});

        enemy.update(delta);
        float enemyX = std::clamp(enemy.getPosition().x, 0.f, scenario.getWidth());
        float enemyY =
            std::clamp(enemy.getPosition().y, scenario.getVerticalBounds(enemy.getPosition().x), windowHeight);
        enemy.setPosition({enemyX, enemyY});

        camera.update(delta);

        // render
        window.draw(scenario);
        window.draw(player);
        window.draw(enemy);

        window.display();
    }

    return 0;
}
