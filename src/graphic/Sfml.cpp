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
            event.mPos = {FROM_PERCENT((double)mouse_pos.x / RESOLUTION.height),
                FROM_PERCENT((double)mouse_pos.y / RESOLUTION.width)};
        }
        if (sfml_event.type == sf::Event::MouseButtonPressed) {
            for (const auto &it : MOUSE_EVENT_LINK) {
                if (sfml_event.mouseButton.button == it.second)
                    event.events.push_back(it.first);
            }
            event.mPos = {FROM_PERCENT((double)mouse_pos.x / RESOLUTION.height),
                FROM_PERCENT((double)mouse_pos.y / RESOLUTION.width)};
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
    for (const auto &entity : entities) {
        std::ifstream inputFile(entity.asset);
        if (inputFile) {
            sf::Texture texture;
            sf::Sprite sprite;
            texture.loadFromFile(entity.asset);
            sf::Vector2u texture_size = texture.getSize();
            sf::Vector2f scaler = {float(entity.size.x / (texture_size.x / INTO_PERCENT(RESOLUTION.width))),
                float(entity.size.y / (texture_size.y / INTO_PERCENT(RESOLUTION.height)))};
            sprite.scale(scaler.x, scaler.y);
            sprite.setTexture(texture);
            sprite.setPosition(entity.pos.x * INTO_PERCENT(window_.getSize().x), entity.pos.y * INTO_PERCENT(window_.getSize().y));
            window_.draw(sprite);
        } else {
            sf::RectangleShape rectangle;
            rectangle.setSize({(float)entity.size.x * INTO_PERCENT(window_.getSize().x), (float)entity.size.y* INTO_PERCENT(window_.getSize().y)});
            rectangle.setFillColor(sf::Color{entity.color.r, entity.color.g, entity.color.b, entity.color.a});
            rectangle.setPosition(entity.pos.x * INTO_PERCENT(window_.getSize().x), entity.pos.y * INTO_PERCENT(window_.getSize().y));
            window_.draw(rectangle);
        }
    }
}

void SFML::createTexts(std::vector <text_t> texts)
{
    for (const auto &element : texts) {
        std::ifstream inputFile(element.fontPath);
        sf::Font font;
        sf::Text text;
        if (inputFile) {
            font.loadFromFile(element.fontPath);
            text.setFont(font);
        }
        if (!element.value.empty()) {
            text.setString(element.value);
        }
        text.setCharacterSize(element.fontSize);
        text.setFillColor((sf::Color) {element.color.r, element.color.g, element.color.b, element.color.a});
        text.setPosition(element.pos.x * INTO_PERCENT(window_.getSize().x), element.pos.y * INTO_PERCENT(window_.getSize().y));
        window_.draw(text);
    }

}

void SFML::display(data_t data)
{
    window_.clear();
    createEntities(data.bg);
    createEntities(data.objects);
    createEntities(data.ui);
    createTexts(data.texts);
    window_.display();
}

extern "C" arcade::IGraphic* makeGraphic()
{
    return new SFML();
}
