/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Minesweeper.cpp
*/

#include "Minesweeper.hpp"

static std::vector<entity_t> create_background(difficulty_t game_params)
{
    std::vector<entity_t> background;
    entity_t temp;
    uint8_t parity;
    
    temp.character = EMPTY_SYMBOL;
    temp.direction = UP;
    for (double line = 0; line < game_params.map_size.first; line++) {
        for (double column = 0; column < game_params.map_size.second; column++) {
            temp.pos = {line, column};
            parity = (((int)line % 2) + (int)column) % 2;
            temp.asset = TILES_ASSETS[parity];
            temp.color = TILES_COLOR[parity];
            background.push_back(temp);
        }
    }
    return background;
}

Minesweeper::Minesweeper()
{
    game_params_ = DIFFICULTY_PARAMS[DEFAULT_DIFFICULTY];
    data_.bg = create_background(game_params_);
}

Minesweeper::~Minesweeper() {}


data_t Minesweeper::update(void)
{
    return data_;
}

extern "C" arcade::IGame* loadingLib() {
    return new Minesweeper();
}
