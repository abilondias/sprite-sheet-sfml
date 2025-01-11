#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>

namespace Game {

    class InputHandler {
    public:
        InputHandler();

        void keyPress(const sf::Event::KeyPressed* e);

        void keyRelease(const sf::Event::KeyReleased* e);

        void mousePress(const sf::Event::MouseButtonPressed* e);

        void mouseRelease(const sf::Event::MouseButtonReleased* e);
    };

} // namespace Game

#endif // INPUTHANDLER_H
