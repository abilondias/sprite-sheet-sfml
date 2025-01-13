#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <SFML/Graphics.hpp>
#include <functional>

#include "State.h"

namespace Game {

    class InputHandler {
    public:
        enum class ActionType { Press, Release };

        enum class Action {
            MoveLeftPress,
            MoveLeftRelease,
            MoveRightPress,
            MoveRightRelease,
            MoveDownPress,
            MoveDownRelease,
            MoveUpPress,
            MoveUpRelease,
            PauseMenuPress,
            PauseMenuRelease,
            AttackPress,
            AttackRelease,
            AltAttackPress,
            AltAttackRelease,
        };

        InputHandler();
        void bindActions();

        void keyPress(const sf::Event::KeyPressed* e);

        void keyRelease(const sf::Event::KeyReleased* e);

        void mousePress(const sf::Event::MouseButtonPressed* e);

        void mouseRelease(const sf::Event::MouseButtonReleased* e);

        // called by entities
        void registerAction(Action action, std::function<void()> fn);

        void setCurrentState(State s) { currentState = s; }

        State getCurrentState() const { return currentState; }

        void processEvent(const std::optional<sf::Event>& event);

    private:
        std::unordered_map<sf::Keyboard::Key, Action> keyPressActions;
        std::unordered_map<sf::Mouse::Button, Action> buttonPressActions;
        std::unordered_map<sf::Keyboard::Key, Action> keyReleaseActions;
        std::unordered_map<sf::Mouse::Button, Action> buttonReleaseActions;

        // TODO: will need to change this part for mouse click position
        std::unordered_map<Action, std::function<void()>> actionCalls;

        State currentState = State::Gameplay;
    };

} // namespace Game

#endif // INPUTHANDLER_H
