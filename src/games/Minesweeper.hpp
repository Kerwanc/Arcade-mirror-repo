/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Minesweeper.hpp
*/

#ifndef MINESWEEPER_H
    #define MINESWEEPER_H
    #define MID_PERCENT 50
    #define MAKE_VECTOR_T(size) (vector_t((double)size, (double)size))
    #define GETBASEPOS(map_size, tile_size) \
    ((double)(MID_PERCENT - map_size * ((double)tile_size / 2)))

    #include "IGame.hpp"
    #include <iostream>
    
typedef struct conf_s {
    std::pair<uint8_t, uint8_t> map_size;
    size_t tile_size;
    size_t mines_nb;
}   conf_t;

enum tile_state_e {
    COVERED,
    DISCOVERED,
    FLAGED
};

typedef struct tile_s {
    tile_state_e state;
    int8_t neighboring_cells;
} tile_t;

class Minesweeper : public arcade::IGame {
    public:
        Minesweeper();
        ~Minesweeper();
        void handleEvent(event_t events) override;
        data_t update(void) override;
        void generateMap(void);
        void insertARandomMine(size_t mines_placed);
        void increaseNeighboringTiles(uint8_t column, uint8_t line);
        void markFlag(double x, double y);
        void removeAnObjectByItsPos(uint8_t x, uint8_t y);
        void handleOver(vector_t mousePos);
    private:
        data_t data_;
        std::vector<std::vector<tile_t>> map_;
        conf_t game_params_;
};

const char EMPTY_SYMBOL = ' ';
const uint8_t DIFFICULTY_AVAILABLE = 2;
const uint8_t DEFAULT_DIFFICULTY = 1;

const conf_t DIFFICULTY_PARAMS[DIFFICULTY_AVAILABLE + 1] {
    {{9, 9}, 3, 10},
    {{16, 16}, 3, 40},
    {{30, 16}, 3, 99}
};

/* COLOR PALETTE */

const color_t TILES_COLOR[2] {
    {178, 255, 101, 255},
    {0, 255, 53, 255}
};

const color_t BACKGROUND_COLOR = {2, 130, 0, 255};
const color_t FLAG_COLOR = {200, 0, 0, 255};

/* ASSETS */

const std::string TILES_ASSETS[2] {
    "",
    ""
};

const std::string BACKGROUND_ASSETS = "";

extern "C" arcade::IGame* makeGame();

#endif /* MINESWEEPER_H */