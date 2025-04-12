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
        x == MAP_SIZE || y == MAP_SIZE)
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
            snake.push_back(createSnakePart('<', YELLOW, SNAKE_START, NEUTRAL_SIZE));
        } else {
            snake.push_back(createSnakePart('X', GREEN, {SNAKE_START.x + i, SNAKE_START.y}, NEUTRAL_SIZE));
        }
    }
    return snake;
}

static vector_t setApplePos(void)
{
    vector_t applePos = {
        ((CENTERING.x + 1) + (rand() % (MAP_SIZE - 1))),
        ((CENTERING.y + 1) + (rand() % (MAP_SIZE - 1)))
    };
    return applePos;
}

static entity_t setApple(void)
{
    entity_t apple;

    apple.asset = TILES_ASSETS.at('O');
    apple.pos = setApplePos();
    apple.color = TILES_COLOR[RED];
    apple.direction = LEFT;
    apple.character = 'O';
    apple.size = NEUTRAL_SIZE;
    return apple;
}

Snake::Snake()
{
    generateMap();
    snake_ = setSnake();
    for (auto snakePart : snake_)
        data_.objects.push_back(snakePart);
    apple_ = setApple();
    data_.objects.push_back(apple_);
    clock_ = 0;
    direction_ = A_KEY_LEFT;
}

void Snake::moveSnake(event_e directionKey)
{
    char headCOntactType = ' ';
    vector_t actualPose = snake_.front().pos;
    vector_t direction = DIRECTIONS_FACTOR.at(directionKey).factor;
    vector_t newPose = {actualPose.x + direction.x,
                        actualPose.y + direction.y};

    headCOntactType = map_[newPose.y - CENTERING.y]
                          [newPose.x - CENTERING.x].type;
    if (headCOntactType!= ' ') {
        map_.clear();
        data_.bg.clear();
        generateMap();
        snake_.clear();
        snake_ = setSnake();
        return;
    }
    snake_.front().character = DIRECTIONS_FACTOR.at(directionKey).character;
    snake_.front().asset = TILES_ASSETS.at(snake_.front().character);
    for (auto &snakePart : snake_) {
        actualPose = snakePart.pos;
        snakePart.pos = newPose;
        newPose = actualPose;
    }
    if (SNAKE_CONTACT(snake_.front().pos, apple_.pos)) {
        snake_.push_back(createSnakePart('X', GREEN, newPose, NEUTRAL_SIZE));
        apple_.pos = setApplePos();
    } else {
        map_[newPose.y - CENTERING.y]
            [newPose.x - CENTERING.x].type = ' ';
    }
    for (auto snakePart : snake_) {
        map_[snakePart.pos.y - CENTERING.y][snakePart.pos.x - CENTERING.x].type
        = snakePart.character;
    }
}

void Snake::handleEvent(event_t latestEvent)
{
    data_.objects.clear();
    for (auto event : latestEvent.events) {
        if (DIRECTIONS_FACTOR.contains(event)) {
            if (OPPOSITES.at(event) != direction_)
                direction_ = event;
        }
    }
    if (clock_ >= 50) {
        moveSnake(direction_);
        clock_ = 0;
    } else {
        clock_ += 1;
    }
    for (auto snakePart : snake_) {
        data_.objects.push_back(snakePart);
    }
    data_.objects.push_back(apple_);
}

static entity_t createBgElement(vector_t size, vector_t pos, char type, color_e color)
{
    entity_t element;

    element.asset = TILES_ASSETS.at(type);
    element.pos = pos;
    element.color = TILES_COLOR[color];
    element.direction = UP;
    element.character = type;
    element.size = size;
    return element;
}

void Snake::generateMap(void)
{
    char type = ' ';
    color_e color = BLACK;
    size_t trueX = 0;
    size_t trueY = 0;

    for (size_t y = 0 ; y <= MAP_SIZE; y++) {
        map_.push_back({});
        for (size_t x = 0 ; x <= MAP_SIZE; x++) {
            trueX = x + CENTERING.x;
            trueY = y + CENTERING.y;
            if (isAtBorder(x, y)) {
                type = '#';
                color = WHITE;
            } else {
                type = ' ';
                color = BLACK;
            }
            map_[y].push_back({{trueX, trueY}, type});
            data_.bg.push_back(createBgElement(NEUTRAL_SIZE,
                {(double)trueX, (double)trueY,}, type, color));
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
