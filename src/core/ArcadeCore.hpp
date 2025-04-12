/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** ArcadeCore
*/

#ifndef ARCADECORE_HPP_
    #define ARCADECORE_HPP_

    #include <iostream>
    #include <memory>
    #include <filesystem>
    #include <algorithm>
    #include "ICore.hpp"
    #include "IGame.hpp"
    #include "IGraphic.hpp"
    constexpr int NB_ARGS = 2;
    constexpr int LIB_PATH_ARG = 1;
    const std::string MENU_PATH = "./lib/arcade_menu.so";

namespace arcade {
    class ArcadeCore : public ICore {
        public:
            ArcadeCore(int argc, const char *argv[]);
            ~ArcadeCore();
            void run();
            void load(std::string libPath, typeLib_e type);
        private:
            bool handleInstructions(const event_t& instructions, const data_t& prevData, const data_t& data);
            void switchGraphicLib();
            void switchGameLib();
            void menuReloading(const data_t& data);
            bool reloadLibs(void);
            std::vector<std::string> allgames_;
            std::vector<std::string> allgraphics_;
            std::string currentLib;
            std::unique_ptr<IGraphic> graphic_;
            std::unique_ptr<IGame> game_;
            int gameIndex;
            int graphicIndex;
    };
}

#endif /* !ARCADECORE_HPP_ */