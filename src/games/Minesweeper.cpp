/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Minesweeper.cpp
*/

#include <stdlib.h>
#include <iostream>
#include <algorithm>

#include "Minesweeper.hpp"

static std::vector<entity_t> createBackground(conf_t game_params)
{
    std::vector<entity_t> background = {};
    entity_t temp = {};
    uint8_t parity = 0;
    vector_t center = {GETBASEPOS(game_params.map_size.first, game_params.tile_size),
        GETBASEPOS(game_params.map_size.second, game_params.tile_size)};

    temp.character = EMPTY_SYMBOL;
    temp.direction = UP;
    temp.size = MAKE_VECTOR_T(game_params.tile_size);
    for (double column = 0; column < game_params.map_size.second; column++) {
        for (double line = 0; line < game_params.map_size.first; line++) {
            temp.pos = {column * game_params.tile_size + center.x, line * game_params.tile_size + center.y};
            parity = (((int)column % 2) + (int)line) % 2;
            temp.asset = TILES_ASSETS[parity];
            temp.color = TILES_COLOR[parity];
            background.push_back(temp);
        }
    }
    return background;
}

void Minesweeper::increaseNeighboringTiles(uint8_t column, uint8_t line)
{
    for (uint8_t y = -1; y != 2; y++) {
        for (uint8_t x = -1; x != 2; x++) {
            if (column + y >= 0 && column + y < game_params_.map_size.second
            && line + x >= 0 && line + x < game_params_.map_size.first)
                if (map_[column + y][line + x].neighboring_cells != -1)
                    map_[column + y][line + x].neighboring_cells++;
        }
    }
}

void Minesweeper::insertARandomMine(size_t mines_placed)
{
    size_t tiles_nb = game_params_.map_size.first * game_params_.map_size.second;
    size_t pos = rand() % (tiles_nb - mines_placed);
    uint8_t column = pos / game_params_.map_size.first;
    uint8_t line = pos % game_params_.map_size.first;

    map_[column][line].neighboring_cells = -1;
    increaseNeighboringTiles(column, line);
}

void Minesweeper::generateMap(void)
{
    for (uint8_t column = 0; column < game_params_.map_size.second; column++) {
        map_.push_back({});
        for (uint8_t line = 0; line < game_params_.map_size.first; line++) {
            map_[column].push_back({COVERED, 0});
        }
    }
    for (size_t mines_placed = 0; mines_placed < game_params_.mines_nb; mines_placed++) {
        insertARandomMine(mines_placed);
    }
}

void Minesweeper::removeAnObjectByItsPos(uint8_t x, uint8_t y)
{
    for(auto it = data_.objects.begin(); it != data_.objects.end(); it++) {
        if (it->pos.x == (double)x
        && it->pos.y == (double)y) {
            data_.objects.erase(it);            
        }
    }
}

void Minesweeper::markFlag(double x, double y)
{
    entity_t flag = {};
    int column = 0;
    int line = 0;
    double index_x = 0;
    double index_y = 0;

    index_x = ((x - GETBASEPOS(game_params_.map_size.first, game_params_.tile_size)) / game_params_.tile_size);
    index_y = ((y - GETBASEPOS(game_params_.map_size.first, game_params_.tile_size)) / game_params_.tile_size);
    column = (int)index_x;
    line = (int)index_y;
    if (index_x < 0 || index_x >= game_params_.map_size.first ||
        index_y < 0 || index_y >= game_params_.map_size.second) {
            return;
        }
    if (map_[column][line].state == DISCOVERED)
        return;
    if (map_[column][line].state == FLAGED) {
        removeAnObjectByItsPos(column, line);
        map_[column][line].state = COVERED;
        return;
    }
    flag.color = FLAG_COLOR;
    flag.character = 'X';
    flag.direction = UP;
    flag.size = MAKE_VECTOR_T(game_params_.tile_size);
    flag.pos = {x, y};
    if (map_[column][line].state == COVERED) {
        map_[column][line].state = FLAGED;
        data_.objects.push_back(flag);
    }
}

Minesweeper::Minesweeper()
{
    game_params_ = DIFFICULTY_PARAMS[DEFAULT_DIFFICULTY];
    data_.bg = createBackground(game_params_);
    generateMap();
    for (size_t i = 0; i < game_params_.map_size.second; i++) {
        for (size_t j = 0; j < game_params_.map_size.first; j++) {
        }
    }
}

Minesweeper::~Minesweeper() {}


data_t Minesweeper::update(void)
{
    return data_;
}

void Minesweeper::handleOver(vector_t mousePos)
{
    for (auto &tale : data_.bg) {
        if (mousePos.x > tale.pos.x && mousePos.x < tale.pos.x + 3
        && mousePos.y > tale.pos.y && mousePos.y < tale.pos.y + 3) {
            tale.color.a = 200;
        }
        else
            tale.color.a = 255;
    }
}

void Minesweeper::handleEvent(event_t CurrentEvent)
{
    for (const auto &event: CurrentEvent.events) {
        if (event == A_MOUSE_MOVE) {
            handleOver(CurrentEvent.mPos);
        }
        if (event == A_MOUSE_LEFT) {
            markFlag(CurrentEvent.mPos.x, CurrentEvent.mPos.y);
        }
    }
}

extern "C" arcade::IGame* makeGame() {
    return new Minesweeper();
}
