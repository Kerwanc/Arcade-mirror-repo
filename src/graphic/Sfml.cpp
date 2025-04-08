/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Sfml.cpp
*/

#include <iostream>

#include "Sfml.hpp"

SFML::SFML() : window_(sf::VideoMode({1920, 1080}), "SFML works!")
{

}

SFML::~SFML()
{
    window_.close();
}

event_t SFML::getEvent()
{
    event_t event;
    sf::Event sfml_event;

    while(window_.pollEvent(sfml_event)) {
        if (sfml_event.type == sf::Event::KeyPressed) {
            for (const auto &it : KEYBOARD_EVENT_LINK) {
                if (sfml_event.key.code == it.second) {
                    event.events.push_back(it.first);
                }
            }
        }
    }
    return event;
}

void SFML::display(data_t data)
{
    window_.clear();
    // window_.draw();
    window_.display();
}

extern "C" arcade::IGraphic* makeGraphic()
{
    return new SFML();
}
