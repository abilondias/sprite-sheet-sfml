#include "Camera.h"

Game::Camera::Camera(Player& p, sf::RenderWindow& w, const float& backgroundWidth) :
    player(p), window(w), maximumViewCenter(backgroundWidth - halfWindowWidth) {}

// view handling based on the background image's size
// move view only when player reaches the thresholds
void Game::Camera::update(const float&) {
    sf::View view = window.getView();
    const float leftThreshold = view.getCenter().x - movementThreshold;
    const float rightThreshold = view.getCenter().x + movementThreshold;
    const float playerX = player.getPosition().x;

    float viewCenterX = view.getCenter().x;
    if (playerX < leftThreshold) {
        viewCenterX = playerX + movementThreshold;
        viewCenterX = std::clamp(viewCenterX, minimumViewCenter, maximumViewCenter);
    } else if (playerX > rightThreshold) {
        viewCenterX = playerX - movementThreshold;
        viewCenterX = std::clamp(viewCenterX, minimumViewCenter, maximumViewCenter);
    }

    view.setCenter({viewCenterX, halfWindowHeight});
    window.setView(view);
}
