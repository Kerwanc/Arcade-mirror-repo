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

    const size_t MAP_SIZE = 30;

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
        void generateMap(void) ;
    private:
        data_t data_;
        std::vector<std::vector<tileInfo_t>> map_;
};

/* ASSETS */

const std::string TILES_ASSETS[2] {
    "",
    ""
};

const std::string BACKGROUND_ASSETS = "";

extern "C" arcade::IGame* makeGame();

#endif /* MINESWEEPER_H */