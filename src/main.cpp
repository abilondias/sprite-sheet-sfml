#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Camera.h"
#include "Enemy.h"
#include "InputHandler.h"
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
    window.setFramerateLimit(60);

    const std::string backgroundTexturePath = "assets/image/brawler/scenario.png";
    const std::string playerTexturePath = "assets/image/brawler/sheet.png";
    const std::string enemyTexturePath = "assets/image/brawler/enemy-sheet1.png";

    constexpr float maxFloat = std::numeric_limits<float>::max();
    Game::Scenario scenario(backgroundTexturePath, window,
                            std::vector{Game::BoundsCheck(30, 315.f),
                                        Game::BoundsCheck(70, Game::InterpolationValues(30, 70, 315, 360)),
                                        Game::BoundsCheck(970, 360.f), Game::BoundsCheck(1225, 260.f),
                                        Game::BoundsCheck(1270, Game::InterpolationValues(1225, 1270, 260, 310)),
                                        Game::BoundsCheck(1520, 310.f), Game::BoundsCheck(maxFloat, 260.f)});

    Game::InputHandler inputHandler;
    Game::Player player(playerTexturePath, scenario); // pass the current scenario to handle bounds
    Game::Enemy enemy(enemyTexturePath, scenario, player);
    Game::Camera camera(player, window, scenario.getWidth());

    player.registerActions(inputHandler);

    inputHandler.registerAction(Game::InputHandler::Action::PauseMenuPress, [&inputHandler]() {
        if (inputHandler.getCurrentState() == Game::State::Gameplay) {
            inputHandler.setCurrentState(Game::State::Menu);
            return;
        }

        inputHandler.setCurrentState(Game::State::Gameplay);
    });

    sf::Clock clock;

    // TODO: create menu view and elements
    auto menu = sf::RectangleShape(sf::Vector2f(window.getSize()));
    auto menuColor = sf::Color(0, 0, 0, 50);
    menu.setFillColor(menuColor);

    float delta = 0;
    while (window.isOpen()) {
        delta = clock.restart().asSeconds();

        while (const auto& e = window.pollEvent()) {
            if (e->is<sf::Event::Closed>()) {
                window.close();
            }

            inputHandler.processEvent(e);
        }

        window.clear();

        if (inputHandler.getCurrentState() == Game::State::Menu) {
            window.draw(menu);
            window.display();
            continue;
        }

        // update game objects
        player.update(delta);
        enemy.update(delta);
        camera.update(delta);

        // render
        window.draw(scenario);
        window.draw(player);
        window.draw(enemy);

        window.display();
    }

    return 0;
}
