#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <SFML/Graphics.hpp>
#include "InputHandler.h"

namespace Game {

    class EventHandler {
    public:
        EventHandler(sf::RenderWindow& w, InputHandler& ih);

        void poll() const;

    private:
        sf::RenderWindow& window;
        InputHandler& inputHandler;
    };

} // namespace Game

#endif // EVENTHANDLER_H
