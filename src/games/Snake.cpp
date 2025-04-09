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

void Snake::generateMap(void)
{
    std::cerr << "ERROR 1" << std::endl;
    for (size_t y = 0; y < MAP_SIZE; y++) {
        map_.push_back({});
        for (size_t x = 0; x < MAP_SIZE; x++) {
            std::cerr << "ERROR 2" << std::endl;
            if (isAtBorder(x, y)) {
                map_[y].push_back({{3 * y, 3 * x}, '#'});
            } else {
                map_[y].push_back({{3 * y, 3 * x}, '#'});;
            }
            std::cerr << map_[y][x].type << " ";
        }
        std::cout << std::endl;
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
