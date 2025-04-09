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

class Menu : public arcade::IGame {
    public:
        Menu();
        ~Menu();
        void handleEvent(event_t events) override;
        data_t update(void) override;
    
    private:
        data_t menu;
        size_t selectedIndex;
        libPaths_t newlibs;
        size_t nbGames;
        size_t nbGraphics;
};

extern "C" arcade::IGame* makeGame();

#endif /* !MENU_HPP_ */
