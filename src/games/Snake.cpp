/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Snake.cpp
*/

#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "Snake.hpp"

bool isAtBorder(size_t x, size_t y)
{
    if (x == 0 || y == 0 ||
        x == MAP_SIZE - 1 || y == MAP_SIZE - 1)
            return true;
    return false;
}

Snake::Snake()
{
}

void Snake::handleEvent(event_t events)
{

}

static entity_t createBgElement(vector_t pos, char type)
{
    entity_t element;

    element.asset = TILES_ASSETS.at(type);
    element.pos = pos;
    element.color = TILES_COLOR[WHITE];
    element.direction = UP;
    element.character = type;
    return element;
}

void Snake::generateMap(void)
{
    char type = ' ';

    for (size_t y = 0; y < MAP_SIZE; y++) {
        map_.push_back({});
        for (size_t x = 0; x < MAP_SIZE; x++) {
            if (isAtBorder(x, y)) {
                type = '#';
            } else {
                type = ' ';
            }
            map_[y].push_back({{3 * y, 3 * x}, type});
            data_.bg.push_back(createBgElement({3.0 * y, 3.0 * x}, type));
        }
    }
}

Snake::~Snake() {}

data_t Snake::update(void)
{
    return data_;
}

extern "C" arcade::IGame* makeGame() {
    return new Snake();
}
