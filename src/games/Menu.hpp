/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** Menu
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <iostream>
    #include <memory>
    #include <filesystem>
    #include <algorithm>
    #include <dlfcn.h>
    #include "IGame.hpp"

    const std::string ARCADE_FONT = "./assets/arcade.ttf";
    const std::string BG_ASSET = "./assets/Arcade_background.png";

class Menu : public arcade::IGame {
    public:
        Menu();
        ~Menu();

        void handleEvent(event_t events) override;
        data_t update(void) override;

    private:
        void setupBackground();
        void setupTitle(double &Pos);
        void loadGames(double &Pos);
        void setupGraphicTitle(double &Pos);
        void loadGraphics(double &Pos);
        void setupCommands(double &Pos);

        data_t menu;
        size_t selectedIndex;
        libPaths_t newlibs;
        size_t nbGames;
        size_t nbGraphics;
};

extern "C" arcade::IGame* makeGame();

#endif /* !MENU_HPP_ */
