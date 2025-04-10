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

static entity_t createSnakePart(char part, color_e color, vector_t pos, vector_t size)
{
    entity_t element;

    element.asset = TILES_ASSETS.at(part);
    element.pos = pos;
    element.color = TILES_COLOR[color];
    element.direction = LEFT;
    element.character = part;
    element.size = size;
    return element;
}

static std::vector<entity_t> setSnake(void)
{
    std::vector<entity_t> snake;

    for (size_t i = 0; i < SNAKE_INIT_SIZE; i++) {
        if (i == 0) {
            snake.push_back(createSnakePart('<', YELLOW, SNAKE_START, {1.0, 1.0}));
        } else {
            snake.push_back(createSnakePart('X', GREEN, {SNAKE_START.x + i, SNAKE_START.y}, {1.0, 1.0}));
        }
    }
    return snake;
}

Snake::Snake()
{
    generateMap();
    snake_ = setSnake();
    for (auto snakePart : snake_)
        data_.objects.push_back(snakePart);
    clock_ = 0;
    direction_ = A_KEY_LEFT;
}

void Snake::moveSnake(event_e directionKey)
{
    vector_t actualPose = snake_.front().pos;
    vector_t direction = DIRECTIONS_RATIO.at(directionKey).ratio;
    vector_t newPose = {actualPose.x + direction.x,
                        actualPose.y + direction.y};

    snake_.front().character = DIRECTIONS_RATIO.at(directionKey).character;
    for (auto &snakePart : snake_) {
        actualPose = snakePart.pos;
        snakePart.pos = newPose;
        newPose = actualPose;
    }
}

void Snake::handleEvent(event_t latestEvent)
{
    data_.objects.clear();

    for (auto event : latestEvent.events) {
        if (DIRECTIONS_RATIO.contains(event)) {
            direction_ = event;
        }
    }
    if (clock_ == 50) {
        moveSnake(direction_);
        clock_ = 0;
    } else {
        clock_ += 1;
    }
    for (auto snakePart : snake_)
        data_.objects.push_back(snakePart);
}

static entity_t createBgElement(vector_t size, vector_t pos, char type)
{
    entity_t element;

    element.asset = TILES_ASSETS.at(type);
    element.pos = pos;
    element.color = TILES_COLOR[WHITE];
    element.direction = UP;
    element.character = type;
    element.size = size;
    return element;
}

void Snake::generateMap(void)
{
    char type = ' ';
    size_t trueX = 0;
    size_t trueY = 0;

    for (size_t y = 0 ; y < MAP_SIZE; y++) {
        map_.push_back({});
        for (size_t x = 0 ; x < MAP_SIZE; x++) {
            trueX = x + CENTERING.x;
            trueY = y + CENTERING.y;
            if (isAtBorder(x, y)) {
                type = '#';
            } else {
                type = ' ';
            }
            map_[y].push_back({{trueY, trueX}, type});
            data_.bg.push_back(createBgElement({1.0, 1.0}, {(double)trueY, (double)trueX}, type));
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
