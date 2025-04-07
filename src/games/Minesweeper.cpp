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
    std::vector<entity_t> background;
    entity_t temp;
    uint8_t parity;
    
    temp.character = EMPTY_SYMBOL;
    temp.direction = UP;
    for (double column = 0; column < game_params.map_size.second; column++) {
        for (double line = 0; line < game_params.map_size.first; line++) {
            temp.pos = {column, line};
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
        for (uint8_t line = 0; line < game_params_.map_size.first; line++) {
            map_[column][line] = {COVERED, 0};
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

void Minesweeper::markFlag(uint8_t x, uint8_t y)
{
    entity_t flag;

    if (map_[y][x].state == DISCOVERED)
        return;
    if (map_[y][x].state == FLAGED) {
        removeAnObjectByItsPos(x, y);
        map_[y][x].state = COVERED;
        return;
    }
    flag.color = FLAG_COLOR;
    flag.character = 'X';
    flag.direction = UP;
    flag.pos = {(double)y, (double)x};
    if (map_[y][x].state == COVERED) {
        map_[y][x].state = FLAGED;
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
            std::cout << map_[i][j].neighboring_cells << " ";
        }
        std::cout << std::endl;
    }
}

Minesweeper::~Minesweeper() {}


data_t Minesweeper::update(void)
{
    return data_;
}

extern "C" arcade::IGame* makeGame() {
    return new Minesweeper();
}
