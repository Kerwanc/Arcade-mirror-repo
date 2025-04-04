/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Minesweeper.hpp
*/

#ifndef MINESWEEPER_H
    #define MINESWEEPER_H

    #include "IGame.hpp"
    #include <iostream>
    
typedef struct difficulty_s {
    std::pair<uint8_t, uint8_t> map_size;
    uint8_t mines_nb;
}   difficulty_t;

class Minesweeper : public arcade::IGame {
    public:
        Minesweeper();
        ~Minesweeper();
        void handleEvent(event_t events) override;
        data_t update(void) override;
    private:
        data_t data_;
        difficulty_t game_params_;
};


const char EMPTY_SYMBOL = 0;
const uint8_t DIFFICULTY_AVAILABLE = 3;
const uint8_t DEFAULT_DIFFICULTY = 1;

const difficulty_t DIFFICULTY_PARAMS[DIFFICULTY_AVAILABLE + 1] {
    {{9, 9}, 10},
    {{16, 16}, 40},
    {{30, 16}, 99}
};

/* COLOR PALETTE */

const color_t TILES_COLOR[2] {
    {178, 255, 101, 255},
    {0, 255, 53, 255}
};

const color_t BACKGROUND_COLOR = {2, 130, 0, 255};

/* ASSETS */

const std::string TILES_ASSETS[2] {
    "",
    ""
};

const std::string BACKGROUND_ASSETS = "";

extern "C" arcade::IGame* loadingLib();

#endif /* MINESWEEPER_H */