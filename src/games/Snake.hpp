/*
** EPITECH PROJECT, 2024
** arcade-mirror-repo
** File description:
** Minesweeper.hpp
*/

#ifndef SNAKE_H
    #define SNAKE_H

    #include "IGame.hpp"
    #include <iostream>
    #include <map>

    const size_t MAP_SIZE = 30;
    const size_t SNAKE_INIT_SIZE = 3;
    const vector_t CENTERING = {50, 10};
    const vector_t SNAKE_START = {50, 50};


typedef struct coord_s {
    size_t x;
    size_t y;
} coord_t;

typedef struct tileInfo_t
{
    coord_t coord;
    char type;
} tileInfo_t;

class Snake : public arcade::IGame {
    public:
        Snake();
        ~Snake();
        void handleEvent(event_t events) override;
        data_t update(void) override;
        void moveSnake(event_e direction);
        void generateMap(void) ;
    private:
        data_t data_;
        size_t clock_;
        event_e direction_;
        std::vector<std::vector<tileInfo_t>> map_;
        std::vector<entity_t> snake_;
};

/* ASSETS */

const std::map<char, std::string> TILES_ASSETS = {
    {'#', " "},
    {' ', " "},
    {'<', " "},
    {'>', " "},
    {'^', " "},
    {'+', " "},
    {'X', " "}
};


typedef struct ratioValues_s {
    char character;
    vector_t ratio;
} ratioValues_t;

const std::map<event_e, ratioValues_t> DIRECTIONS_RATIO =
{
    {A_KEY_DOWN, {'+', {0.0, 1}}},
    {A_KEY_LEFT, {'<', {-1, 0.0}}},
    {A_KEY_RIGHT, {'>', {1, 0.0}}},
    {A_KEY_UP, {'^', {0.0, -1}}}
};

enum color_e {
    WHITE,
    BLACK,
    RED,
    GREEN,
    YELLOW
};

const color_t TILES_COLOR[] {
    {255, 255, 255, 255},
    {0, 0, 0, 255},
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {255, 255, 0, 255}
};

const std::string BACKGROUND_ASSETS = "";

extern "C" arcade::IGame* makeGame();

#endif /* MINESWEEPER_H */