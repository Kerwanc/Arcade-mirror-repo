/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Sfml.cpp
*/

#include <iostream>
#include <fstream>

#include "Sfml.hpp"

SFML::SFML() : window_(RESOLUTION, "SFML works!")
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
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window_);

    while(window_.pollEvent(sfml_event)) {
        if (sfml_event.type == sf::Event::MouseMoved) {
            event.events.push_back(A_MOUSE_MOVE);
            event.mPos = {(double)mouse_pos.x / RESOLUTION.height * 100,
                (double)mouse_pos.y / RESOLUTION.width * 100};
        }
        if (sfml_event.type == sf::Event::MouseButtonPressed) {
            for (const auto &it : MOUSE_EVENT_LINK) {
                if (sfml_event.mouseButton.button == it.second)
                    event.events.push_back(it.first);
            }
            event.mPos = {(double)mouse_pos.x / RESOLUTION.height * 100,
                (double)mouse_pos.y / RESOLUTION.width * 100};
        }
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

void SFML::createEntities(std::vector<entity_t> entities)
{
    std::vector<sf::Texture> textures;
    sf::RectangleShape rectangle;
    sf::Texture texture;

    for (const auto &entity : entities) {
        std::ifstream inputFile(entity.asset);
        if (inputFile) {
        } else {
            rectangle.setSize({(float)entity.size.x* window_.getSize().x / 100, (float)entity.size.y* window_.getSize().y / 100});
            rectangle.setFillColor(sf::Color{entity.color.r, entity.color.g, entity.color.b, entity.color.a});
            rectangle.setPosition(entity.pos.x * window_.getSize().x / 100, entity.pos.y * window_.getSize().y / 100);
            rectangles_.push_back(rectangle);
        }
    }
}

void SFML::display(data_t data)
{
    rectangles_.clear();
    sprites_.clear();
    createEntities(data.bg);
    createEntities(data.objects);
    createEntities(data.ui);
    window_.clear();
    for (const auto &sprite : sprites_) {
        window_.draw(sprite);
    }
    for (const auto &rectangle : rectangles_) {
        window_.draw(rectangle);
    }
    window_.display();
}

extern "C" arcade::IGraphic* makeGraphic()
{
    return new SFML();
}
