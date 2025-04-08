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
    private:
        sf::RenderWindow window_;
};

const std::map<event_e, sf::Keyboard::Key> KEYBOARD_EVENT_LINK =
{
    {A_KEY_A, sf::Keyboard::A},
    {A_KEY_ESC, sf::Keyboard::Escape},
    {A_KEY_UP, sf::Keyboard::Up},
    {A_KEY_LEFT, sf::Keyboard::Left},
    {A_KEY_RIGHT, sf::Keyboard::Right},
    {A_KEY_DOWN, sf::Keyboard::Down}
};

extern "C" arcade::IGraphic* makeGraphic();

#endif /* SFML_H */