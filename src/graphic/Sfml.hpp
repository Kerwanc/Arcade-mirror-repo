/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Sfml.hpp
*/

#ifndef SFML_H
    #define SFML_H

    #include <SFML/Window.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window/Event.hpp>
    #include "IGraphic.hpp"

class SFML : public arcade::IGraphic {
    public:
        SFML();
        ~SFML();
        event_t getEvent(void) override;
        void display(data_t data) override;
        void createEntities(std::vector<entity_t> entities);
    private:
        sf::RenderWindow window_;
        std::vector<sf::Sprite> sprites_;
        std::vector<sf::RectangleShape> rectangles_;
};

const std::map<event_e, sf::Keyboard::Key> KEYBOARD_EVENT_LINK =
{
    {A_KEY_A, sf::Keyboard::A},
    {A_KEY_ESC, sf::Keyboard::Escape},
    {A_KEY_UP, sf::Keyboard::Up},
    {A_KEY_LEFT, sf::Keyboard::Left},
    {A_KEY_RIGHT, sf::Keyboard::Right},
    {A_KEY_DOWN, sf::Keyboard::Down},
    {A_KEY_ENTER, sf::Keyboard::Enter}
};

const std::map<event_e, sf::Mouse::Button> MOUSE_EVENT_LINK =
{
    {A_MOUSE_LEFT, sf::Mouse::Left},
    {A_MOUSE_RIGHT, sf::Mouse::Right}
};

const sf::VideoMode RESOLUTION = {1000, 1000};

extern "C" arcade::IGraphic* makeGraphic();

#endif /* SFML_H */