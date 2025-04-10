/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Minesweeper.cpp
*/

#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <map>

#include "Minesweeper.hpp"

static std::vector<entity_t> createBackground(conf_t game_params)
{
    std::vector<entity_t> background = {};
    entity_t temp = {};
    uint8_t parity = 0;
    vector_t center = {GETBASEPOS(game_params.map_size.second, game_params.tile_size),
        GETBASEPOS(game_params.map_size.first, game_params.tile_size)};

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

void Minesweeper::removeAnObjectByItsPos(int x, int y)
{
    size_t index = 0;

    for(auto it : data_.objects) {
        if ((int)it.pos.x == x
            && (int)it.pos.y == y) {
                data_.objects.erase(data_.objects.begin() + index);
            }
        index++;
    }
}

void Minesweeper::markFlag(vector_t mousePos)
{
    entity_t flag = {};
    int column = 0;
    int line = 0;

    mousePos.x = PERCENTTOINDEX(mousePos.x, game_params_.map_size.second, game_params_.tile_size);
    mousePos.y = PERCENTTOINDEX(mousePos.y, game_params_.map_size.first, game_params_.tile_size);
    column = (int)mousePos.x;
    line = (int)mousePos.y;
    if (mousePos.x < 0 || mousePos.x >= game_params_.map_size.second ||
        mousePos.y < 0 || mousePos.y >= game_params_.map_size.first) {
            return;
        }
    mousePos.x = INDEXTOPERCENT(column, game_params_.map_size.second, game_params_.tile_size);
    mousePos.y = INDEXTOPERCENT(line, game_params_.map_size.first, game_params_.tile_size);
    if (map_[column][line].state == DISCOVERED)
        return;
    if (map_[column][line].state == FLAGED) {
        removeAnObjectByItsPos(mousePos.x, mousePos.y);
        map_[column][line].state = COVERED;
        return;
    }
    flag.color = FLAG_COLOR;
    flag.character = 'X';
    flag.direction = UP;
    flag.size = MAKE_VECTOR_T(game_params_.tile_size);
    flag.pos = {mousePos.x, mousePos.y};
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
        if (mousePos.x > tale.pos.x && mousePos.x < tale.pos.x + game_params_.tile_size
        && mousePos.y > tale.pos.y && mousePos.y < tale.pos.y + game_params_.tile_size) {
            tale.color.a = 200;
        }
        else
            tale.color.a = 255;
    }
}

void Minesweeper::dig(vector_2int_t pos)
{
    entity_t tale = {};

    tale.asset = ITEMS_ASSETS.find(map_[pos.x][pos.y].neighboring_cells)->second.asset;
    tale.character = ITEMS_ASSETS.find(map_[pos.x][pos.y].neighboring_cells)->second.character;
    tale.color = ITEMS_ASSETS.find(map_[pos.x][pos.y].neighboring_cells)->second.color;
    tale.direction = UP;
    tale.pos.x = INDEXTOPERCENT(pos.x, game_params_.map_size.second, game_params_.tile_size);
    tale.pos.y = INDEXTOPERCENT(pos.y, game_params_.map_size.first, game_params_.tile_size);
    tale.size = MAKE_VECTOR_T(game_params_.tile_size / 5);
    data_.objects.push_back(tale);
    map_[pos.x][pos.y].state = DISCOVERED;
}

void Minesweeper::handleLeftClick(vector_t mousePos)
{
    vector_t coordinate_on_map = {PERCENTTOINDEX(mousePos.x, game_params_.map_size.second,
        game_params_.tile_size), PERCENTTOINDEX(mousePos.y, game_params_.map_size.first,
        game_params_.tile_size)};
    int column = (int)coordinate_on_map.x;
    int line = (int)coordinate_on_map.y;

    if (coordinate_on_map.x < 0 || coordinate_on_map.x > game_params_.map_size.second
        || coordinate_on_map.y < 0 || coordinate_on_map.y > game_params_.map_size.first)
        return;
    if (map_[column][line].state == COVERED) {
        dig({column, line});
    }
}

void Minesweeper::handleEvent(event_t CurrentEvent)
{
    for (const auto &event: CurrentEvent.events) {
        for (const auto &link : EVENT_HANDLER) {
            if (event == link.first) {
                link.second(*this, CurrentEvent.mPos);
            }
        }
    }
}

extern "C" arcade::IGame* makeGame() {
    return new Minesweeper();
}
