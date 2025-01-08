#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "src/Background.h"
#include "src/Camera.h"
#include "src/Player.h"

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

    Game::Background background(backgroundTexturePath, window);
    Game::Player player(playerTexturePath, background.scale);
    Game::Camera camera(player, window, background.width);

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
        float playerX = std::clamp(player.getPosition().x, 0.f, background.width);
        // TODO: use vertex array to create vertical bounds matching the background
        float playerY = std::clamp(player.getPosition().y, 0.f, windowHeight);
        player.setPosition({playerX, playerY});
        camera.update(delta);

        // render
        window.draw(background);
        window.draw(player);

        window.display();
    }

    return 0;
}
