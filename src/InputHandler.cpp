#include "InputHandler.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Game::InputHandler::InputHandler() = default;

void Game::InputHandler::keyPress(const sf::Event::KeyPressed* e) {
    switch (e->code) {
    case sf::Keyboard::Key::W:
        std::cout << "W down\n";
        break;
    case sf::Keyboard::Key::D:
        std::cout << "D down\n";
        break;
    case sf::Keyboard::Key::A:
        std::cout << "A down\n";
        break;
    case sf::Keyboard::Key::S:
        std::cout << "S down\n";
        break;
    default:
        break;
    }
}

void Game::InputHandler::keyRelease(const sf::Event::KeyReleased* e) {
    switch (e->code) {
    case sf::Keyboard::Key::W:
        std::cout << "W up\n";
        break;
    case sf::Keyboard::Key::D:
        std::cout << "D up\n";
        break;
    case sf::Keyboard::Key::A:
        std::cout << "A up\n";
        break;
    case sf::Keyboard::Key::S:
        std::cout << "S up\n";
        break;
    default:
        break;
    }
}

void Game::InputHandler::mousePress(const sf::Event::MouseButtonPressed* e) {
    switch (e->button) {
    case sf::Mouse::Button::Left:
        std::cout << "left button press\n";
        break;
    case sf::Mouse::Button::Middle:
        std::cout << "middle button press\n";
        break;
    case sf::Mouse::Button::Right:
        std::cout << "right button press\n";
        break;
    default:
        break;
    }
}

void Game::InputHandler::mouseRelease(const sf::Event::MouseButtonReleased* e) {
    switch (e->button) {
    case sf::Mouse::Button::Left:
        std::cout << "left button release\n";
        break;
    case sf::Mouse::Button::Middle:
        std::cout << "middle button release\n";
        break;
    case sf::Mouse::Button::Right:
        std::cout << "right button release\n";
        break;
    default:
        break;
    }
}
