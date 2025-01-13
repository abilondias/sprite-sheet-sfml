#include "InputHandler.h"

#include <SFML/Graphics.hpp>
#include <iostream>

Game::InputHandler::InputHandler() { bindActions(); };

void Game::InputHandler::bindActions() {
    using namespace sf::Keyboard;
    using namespace sf::Mouse;

    keyPressActions[Key::A] = Action::MoveLeftPress;
    keyReleaseActions[Key::A] = Action::MoveLeftRelease;
    keyPressActions[Key::D] = Action::MoveRightPress;
    keyReleaseActions[Key::D] = Action::MoveRightRelease;
    keyPressActions[Key::S] = Action::MoveDownPress;
    keyReleaseActions[Key::S] = Action::MoveDownRelease;
    keyPressActions[Key::W] = Action::MoveUpPress;
    keyReleaseActions[Key::W] = Action::MoveUpRelease;
    keyPressActions[Key::Escape] = Action::PauseMenuPress;
    keyReleaseActions[Key::Escape] = Action::PauseMenuRelease;
    buttonPressActions[Button::Left] = Action::AttackPress;
    buttonReleaseActions[Button::Left] = Action::AttackRelease;
    buttonPressActions[Button::Right] = Action::AltAttackPress;
    buttonReleaseActions[Button::Right] = Action::AltAttackRelease;
}

void Game::InputHandler::registerAction(Action action, std::function<void()> fn) { actionCalls[action] = fn; }

void Game::InputHandler::processEvent(const std::optional<sf::Event>& event) {
    if (const auto mbp = event->getIf<sf::Event::MouseButtonPressed>()) {
        mousePress(mbp);
    } else if (const auto mbr = event->getIf<sf::Event::MouseButtonReleased>()) {
        mouseRelease(mbr);
    } else if (const auto kp = event->getIf<sf::Event::KeyPressed>()) {
        keyPress(kp);
    } else if (const auto kr = event->getIf<sf::Event::KeyReleased>()) {
        keyRelease(kr);
    }
}

void Game::InputHandler::keyPress(const sf::Event::KeyPressed* e) {
    const auto it = keyPressActions.find(e->code);
    if (it == keyPressActions.end()) {
        return;
    }
    if (const auto fn = actionCalls.find(it->second); fn != actionCalls.end()) {
        fn->second();
    }
}

void Game::InputHandler::keyRelease(const sf::Event::KeyReleased* e) {
    const auto it = keyReleaseActions.find(e->code);
    if (it == keyReleaseActions.end()) {
        return;
    }
    if (const auto fn = actionCalls.find(it->second); fn != actionCalls.end()) {
        fn->second();
    }
}

void Game::InputHandler::mousePress(const sf::Event::MouseButtonPressed* e) {
    const auto it = buttonPressActions.find(e->button);
    if (it == buttonPressActions.end()) {
        return;
    }
    if (const auto fn = actionCalls.find(it->second); fn != actionCalls.end()) {
        fn->second(); // TODO: mouse click position: e->position
    }
}

void Game::InputHandler::mouseRelease(const sf::Event::MouseButtonReleased* e) {
    const auto it = buttonReleaseActions.find(e->button);
    if (it == buttonReleaseActions.end()) {
        return;
    }
    if (const auto fn = actionCalls.find(it->second); fn != actionCalls.end()) {
        fn->second();
    }
}
