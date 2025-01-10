#ifndef CAMERA_H
#define CAMERA_H

#include "Player.h"

namespace Game {
    class Camera {
    public:
        Camera(Player& p, sf::RenderWindow& w, const float& scenarioWidth); // Player here could be a "Focusable"

        void update(const float& delta);
    private:
        Player& player;
        sf::RenderWindow& window;

        // used to calculate the point near the edges where the camera should move when following the player
        // 0.4 is for 40% from the center, so the thresholds are the point at 10% of both sides
        const float movementThreshold = 0.4f * window.getSize().x;

        const float halfWindowWidth = window.getSize().x * 0.5f;
        const float halfWindowHeight = window.getSize().y * 0.5f;

        // lowest possible horizontal point so the view doesn't go out of the scenario's bounds
        // assuming there's no texture repeat, going to half window width - 50px,
        // means 50px of the left side won't render anything meaningful
        const float minimumViewCenter = halfWindowWidth;
        const float maximumViewCenter; // calculated using the specified scenario's width
    };
} // namespace Game

#endif // CAMERA_H
