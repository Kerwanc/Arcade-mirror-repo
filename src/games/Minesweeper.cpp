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
    for (int mines_placed = 0; mines_placed < game_params_.mines_nb; mines_placed++) {
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

void Minesweeper::createUi()
{
    entity_t ui_background = {};
    entity_t ui_flag = {};
    text_t flag_nb = {};
    text_t score = {};
    text_t end = {};

    ui_background.character = EMPTY_SYMBOL;
    ui_background.color = UI_BACKGROUND_COLOR;
    ui_background.direction = UP;
    ui_background.pos.x = GETBASEPOS(game_params_.map_size.second, game_params_.tile_size);
    ui_background.pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_PADDING * game_params_.tile_size;
    ui_background.size.x = game_params_.tile_size * game_params_.map_size.second;
    ui_background.size.y = UI_PADDING * game_params_.tile_size;
    ui_flag.asset = FLAG_INFO_DISPLAY.asset;
    ui_flag.character = FLAG_INFO_DISPLAY.character;
    ui_flag.color = FLAG_INFO_DISPLAY.color;
    ui_flag.direction = UP;
    ui_flag.pos.x = UI_FLAG_POS;
    ui_flag.pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_ITEM_PADDING * game_params_.tile_size;
    ui_flag.size = MAKE_VECTOR_T(game_params_.tile_size * UI_SPRITE_SIZE_MULTIPLIER);
    flag_nb.color = UI_FLAG_NB_COLOR;
    flag_nb.fontPath = MINESWEEPER_FONT;
    flag_nb.fontSize = MINESWEEPER_FONT_SIZE * game_params_.tile_size;
    flag_nb.pos.x = UI_FLAG_NB_POS;
    flag_nb.pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_TEXT_PADDING * game_params_.tile_size;
    flag_nb.value = std::to_string(game_params_.mines_nb);
    score.color = UI_SCORE_COLOR;
    score.fontPath = MINESWEEPER_FONT;
    score.fontSize = MINESWEEPER_FONT_SIZE * game_params_.tile_size;
    score.pos.x = UI_SCORE_POS;
    score.pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_TEXT_PADDING * game_params_.tile_size;
    score.value = SCORE_TEXT_VALUE;
    score.value.append(std::to_string(score_));
    end.fontPath = MINESWEEPER_FONT;
    end.fontSize = MINESWEEPER_FONT_SIZE * game_params_.tile_size;
    end.pos.x = UI_END_POS;
    end.pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) -  UI_TEXT_PADDING * game_params_.tile_size * 1.5;
    data_.ui.push_back(ui_background);
    data_.ui.push_back(ui_flag);
    data_.texts.push_back(flag_nb);
    data_.texts.push_back(score);
    data_.texts.push_back(end);
}

void Minesweeper::updateMineDisplayer()
{
    vector_t pos;

    pos.x = UI_FLAG_NB_POS;
    pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_TEXT_PADDING * game_params_.tile_size;
    for (auto &it : data_.texts) {
        if (pos.x == it.pos.x && pos.y == it.pos.y)
            it.value = std::to_string(game_params_.mines_nb);
    }
}

void Minesweeper::updateScoreDisplayer()
{
    vector_t pos;

    pos.x = UI_SCORE_POS;
    pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_TEXT_PADDING * game_params_.tile_size;
    for (auto &it : data_.texts) {
        if (pos.x == it.pos.x && pos.y == it.pos.y) {
            it.value = SCORE_TEXT_VALUE;
            it.value.append(std::to_string(score_));
        }
    }
}

void Minesweeper::endDisplayer(std::string message, color_t message_color)
{
    vector_t pos;

    pos.x = UI_END_POS;
    pos.y = GETBASEPOS(game_params_.map_size.first, game_params_.tile_size) - UI_TEXT_PADDING * game_params_.tile_size * 1.5;
    for (auto &it : data_.texts) {
        if (pos.x == it.pos.x && pos.y == it.pos.y) {
            it.value = message;
            it.color = message_color;
        }
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
        game_params_.mines_nb++;
        updateMineDisplayer();
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
    updateMineDisplayer();
}

void Minesweeper::changeDifficulty(vector_t)
{
    map_.clear();
    data_.bg.clear();
    data_.objects.clear();
    data_.ui.clear();
    data_.audios.clear();
    data_.texts.clear();
    start_digging_ = UNDEFINED;
    difficulty_++;
    if (difficulty_ > 2)
        difficulty_ = 0;
    game_params_ = DIFFICULTY_PARAMS[difficulty_];
    data_.bg = createBackground(game_params_);
    endDisplayer("", UI_WIN_COLOR);
    createUi();
    generateMap();
}

void Minesweeper::restart(vector_t)
{
    map_.clear();
    data_.bg.clear();
    data_.objects.clear();
    data_.ui.clear();
    data_.audios.clear();
    data_.texts.clear();
    start_digging_ = UNDEFINED;
    game_params_ = DIFFICULTY_PARAMS[difficulty_];
    data_.bg = createBackground(game_params_);
    score_ = 0;
    endDisplayer("", UI_WIN_COLOR);
    createUi();
    generateMap();
}

Minesweeper::Minesweeper() : start_digging_(UNDEFINED), difficulty_(DEFAULT_DIFFICULTY), score_(0)
{
    game_params_ = DIFFICULTY_PARAMS[difficulty_];
    data_.bg = createBackground(game_params_);
    createUi();
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

void Minesweeper::reveal_cell(vector_2int_t pos)
{
    entity_t tale = {};

    tale.asset = ITEMS_INFO_DISPLAY.find(map_[pos.x][pos.y].neighboring_cells)->second.asset;
    tale.character = ITEMS_INFO_DISPLAY.find(map_[pos.x][pos.y].neighboring_cells)->second.character;
    tale.color = ITEMS_INFO_DISPLAY.find(map_[pos.x][pos.y].neighboring_cells)->second.color;
    tale.direction = UP;
    tale.pos.x = INDEXTOPERCENT(pos.x, game_params_.map_size.second, game_params_.tile_size);
    tale.pos.y = INDEXTOPERCENT(pos.y, game_params_.map_size.first, game_params_.tile_size);
    tale.size = MAKE_VECTOR_T(game_params_.tile_size);
    data_.objects.push_back(tale);
    map_[pos.x][pos.y].state = DISCOVERED;
}

void Minesweeper::lose()
{
    for (uint8_t column = 0; column < game_params_.map_size.second; column++) {
        for (uint8_t line = 0; line < game_params_.map_size.first; line++) {
            if (map_[column][line].neighboring_cells == MINE) {
                reveal_cell({column, line});
            }
            map_[column][line].state = DISCOVERED;
        }
    }
    score_ = 0;
    endDisplayer(LOSE_TEXT_VALUE, UI_LOSE_COLOR);
}


void Minesweeper::dig(vector_2int_t pos)
{
    if (start_digging_ == UNDEFINED) {
        placeMines(pos);
        start_digging_ = FALSE;
    }
    if (map_[pos.x][pos.y].state != COVERED) {
        return;
    }
    if (start_digging_ == TRUE) {
        score_ += SCORE_INCREMENTER;
    }
    reveal_cell(pos);
    if (map_[pos.x][pos.y].neighboring_cells == MINE) {
        lose();
    }
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
        if (start_digging_ == FALSE) {
            start_digging_ = TRUE;
        }
        dig({column, line});
        updateScoreDisplayer();
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
