#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "Background.h"
#include "Camera.h"
#include "Player.h"

float interpolate(float x, float t1, float t2, float s1, float s2) {
    const float f = (x - t1) / (t2 - t1);
    const float g = f * (s2 - s1) + s1;
    return g;
}

float getScenarioBoundary(const sf::Vector2f& position) {
    float x = position.x;
    if (x < 30) return 315;
    // interpolate here so it can generate diagonal height values between points 30 and 70
    if (x < 70) return interpolate(x, 30, 70, 315, 360);
    if (x < 970) return 360;
    if (x < 1225) return 260;
    if (x < 1270) return interpolate(x, 1225, 1270, 260, 310);
    if (x < 1520) return 310;
    return 260;
}

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
        float playerY = std::clamp(player.getPosition().y, getScenarioBoundary(player.getPosition()), windowHeight);
        player.setPosition({playerX, playerY});
        camera.update(delta);

        // render
        window.draw(background);
        window.draw(player);

        window.display();
    }

    return 0;
}
