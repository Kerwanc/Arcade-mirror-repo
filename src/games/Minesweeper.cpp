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
    temp.pos = MAKE_VECTOR_T(DEFAULT_POS);
    temp.size = MAKE_VECTOR_T(FILL_SIZE);
    temp.color = BACKGROUND_COLOR;
    background.push_back(temp);
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
    for (int8_t y = -1; y != 2; y++) {
        for (int8_t x = -1; x != 2; x++) {
            if (column + y >= 0 && column + y < game_params_.map_size.second
            && line + x >= 0 && line + x < game_params_.map_size.first)
                if (map_[column + y][line + x].neighboring_cells != MINE)
                    map_[column + y][line + x].neighboring_cells++;
        }
    }
}

static bool is_surrounding(vector_2int_t tile, vector_2int_t pos)
{
    for (int8_t y = -1; y != 2; y++) {
        for (int8_t x = -1; x != 2; x++) {
            if (tile.x + x == pos.x && tile.y + y == pos.y)
                return true;
        }
    }
    return false;
}

void Minesweeper::insertARandomMine(size_t mines_placed, vector_2int_t pos)
{
    size_t tiles_nb = game_params_.map_size.first * game_params_.map_size.second;
    size_t mine_pos = rand() % (tiles_nb - mines_placed - 9);
    uint8_t column;
    uint8_t line;
    size_t index = 0;

    for (column = 0; column < game_params_.map_size.second; column++) {
        for (line = 0; line < game_params_.map_size.first; line++) {
            if (map_[column][line].neighboring_cells == MINE)
                continue;
            if (is_surrounding({column, line}, pos) == true) {
                continue;
            }
            if (index == mine_pos) {
                map_[column][line].neighboring_cells = MINE;
                increaseNeighboringTiles(column, line);
                return;
            }
            index++;
        }
    }
}

void Minesweeper::placeMines(vector_2int_t pos)
{
    for (size_t mines_placed = 0; mines_placed < game_params_.mines_nb; mines_placed++) {
        insertARandomMine(mines_placed, pos);
    }
}

void Minesweeper::generateMap(void)
{
    map_.resize(game_params_.map_size.second);
    for (auto &it : map_) {
        it.resize(game_params_.map_size.first, {COVERED, EMPTY_TILE});
    }
}

void Minesweeper::updateMineDisplayer()
{
    
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
        game_params_.mines_nb++;
        return;
    }
    game_params_.mines_nb--;
    flag.asset = FLAG_INFO_DISPLAY.asset;
    flag.character = FLAG_INFO_DISPLAY.character;
    flag.color = FLAG_INFO_DISPLAY.color;
    flag.direction = UP;
    flag.size = MAKE_VECTOR_T(game_params_.tile_size);
    flag.pos = {mousePos.x, mousePos.y};
    if (map_[column][line].state == COVERED) {
        map_[column][line].state = FLAGED;
        data_.objects.push_back(flag);
    }
}

Minesweeper::Minesweeper() : start_digging_(false)
{
    game_params_ = DIFFICULTY_PARAMS[DEFAULT_DIFFICULTY];
    data_.bg = createBackground(game_params_);
    
    generateMap();
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
            tale.color.a = OVER_OPACITY;
        }
        else
            tale.color.a = MAX_OPACITY;
    }
}

void Minesweeper::dig(vector_2int_t pos)
{
    entity_t tale = {};

    if (start_digging_ == false) {
        placeMines(pos);
        start_digging_ = true;
    }
    if (map_[pos.x][pos.y].state != COVERED) {
        return;
    }
    tale.asset = ITEMS_INFO_DISPLAY.find(map_[pos.x][pos.y].neighboring_cells)->second.asset;
    tale.character = ITEMS_INFO_DISPLAY.find(map_[pos.x][pos.y].neighboring_cells)->second.character;
    tale.color = ITEMS_INFO_DISPLAY.find(map_[pos.x][pos.y].neighboring_cells)->second.color;
    tale.direction = UP;
    tale.pos.x = INDEXTOPERCENT(pos.x, game_params_.map_size.second, game_params_.tile_size);
    tale.pos.y = INDEXTOPERCENT(pos.y, game_params_.map_size.first, game_params_.tile_size);
    tale.size = MAKE_VECTOR_T(game_params_.tile_size);
    data_.objects.push_back(tale);
    map_[pos.x][pos.y].state = DISCOVERED;
    if (map_[pos.x][pos.y].neighboring_cells != EMPTY_TILE) {
        return;
    }
    for (int8_t y = -1; y != 2; y++) {
        for (int8_t x = -1; x != 2; x++) {
            if (pos.x + x >= 0 && pos.x + x < game_params_.map_size.second
            && pos.y + y >= 0 && pos.y + y < game_params_.map_size.first) {
                dig({pos.x + x, pos.y + y});
            }
                
        }
    }
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

void Minesweeper::switchToMenu(vector_t)
{
    data_.libs.game = MENU_PATH;
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
