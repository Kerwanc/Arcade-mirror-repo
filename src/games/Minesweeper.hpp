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
    #define PERCENTTOINDEX(pos, map_size, tile_size) (double( \
        (pos - GETBASEPOS(map_size, tile_size)) / tile_size))
    #define INDEXTOPERCENT(index, map_size, tile_size) (double( \
        (index * tile_size + GETBASEPOS(map_size, tile_size))))

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

typedef struct vector_2int_s {
    int x;
    int y;
} vector_2int_t;

class Minesweeper : public arcade::IGame {
    public:
        Minesweeper();
        ~Minesweeper();
        void handleEvent(event_t events) override;
        data_t update(void) override;
        void generateMap(void);
        void insertARandomMine(size_t mines_placed);
        void increaseNeighboringTiles(uint8_t column, uint8_t line);
        void removeAnObjectByItsPos(int x, int y);
        void handleOver(vector_t mousePos);
        void markFlag(vector_t mousePos);
        void handleLeftClick(vector_t mousePos);
        void dig(vector_2int_t pos);
    private:
        data_t data_;
        std::vector<std::vector<tile_t>> map_;
        conf_t game_params_;
        const std::map<event_e, std::function<void(Minesweeper &, vector_t)>> EVENT_HANDLER =
        {
            {A_MOUSE_MOVE, &Minesweeper::handleOver},
            {A_MOUSE_LEFT, &Minesweeper::handleLeftClick},
            {A_MOUSE_RIGHT, &Minesweeper::markFlag}
        };
};

const char EMPTY_SYMBOL = ' ';
const uint8_t DIFFICULTY_AVAILABLE = 2;
const uint8_t DEFAULT_DIFFICULTY = 2;

const conf_t DIFFICULTY_PARAMS[DIFFICULTY_AVAILABLE + 1] {
    {{9, 9}, 5, 10},
    {{16, 16}, 4, 40},
    {{16, 30}, 3, 99}
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

typedef struct info_display_s {
    std::string asset;
    char character;
    color_t color;
} info_display_t;

const std::map<int8_t, info_display_t> ITEMS_ASSETS =
{
    {-1, {"./lib/assets/arcade_minesweeper/mine.png", 'O', {0, 0, 0, 255}}},
    {0, {"./lib/assets/arcade_minesweeper/empty_tile.png", ' ', {0xff, 0xff, 0xff, 255}}},
    {1, {"./lib/assets/arcade_minesweeper/tile_1.png", '1', {0x66, 0x8b, 0xe7, 255}}},
    {2, {"./lib/assets/arcade_minesweeper/tile_2.png", '2', {0x7f, 0xea, 0xe5, 255}}},
    {3, {"./lib/assets/arcade_minesweeper/tile_3.png", '3', {0x20, 0xef, 0x7d, 255}}},
    {4, {"./lib/assets/arcade_minesweeper/tile_4.png", '4', {0x9d, 0xef, 0xd0, 255}}},
    {5, {"./lib/assets/arcade_minesweeper/tile_5.png", '5', {0xef, 0xc9, 0x20, 255}}},
    {6, {"./lib/assets/arcade_minesweeper/tile_6.png", '6', {0xe9, 0x61, 0x13, 255}}},
    {7, {"./lib/assets/arcade_minesweeper/tile_7.png", '7', {0xf2, 0x0c, 0x03, 255}}},
    {8, {"./lib/assets/arcade_minesweeper/tile_8.png", '8', {0xf2, 0x03, 0xd7, 255}}}
};

extern "C" arcade::IGame* makeGame();

#endif /* MINESWEEPER_H */