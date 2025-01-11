#include "EventHandler.h"
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

Game::EventHandler::EventHandler(sf::RenderWindow& w, InputHandler& ih) : window(w), inputHandler(ih) {}

void Game::EventHandler::poll() const {
    while (const auto& event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else if (auto mbp = event->getIf<sf::Event::MouseButtonPressed>()) {
            inputHandler.mousePress(mbp);
        } else if (auto mbr = event->getIf<sf::Event::MouseButtonReleased>()) {
            inputHandler.mouseRelease(mbr);
        } else if (auto kp = event->getIf<sf::Event::KeyPressed>()) {
            inputHandler.keyPress(kp);
        } else if (auto kr = event->getIf<sf::Event::KeyReleased>()) {
            inputHandler.keyRelease(kr);
        }
    }
}
