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
    #include "ICore.hpp"
    #include "IGame.hpp"
    #include "IGraphic.hpp"
    constexpr int NB_ARGS = 2;
    constexpr int LIB_PATH_ARG = 1;

namespace arcade {
    class ArcadeCore : public ICore {
        public:
            ArcadeCore(int argc, const char *argv[]);
            ~ArcadeCore() = default;
            void run();
            void load(std::string libPath, typeLib_e type);
        private:
            std::string currentLib;
            std::unique_ptr<IGraphic> graphic_;
            std::unique_ptr<IGame> game_;
    };
}

#endif /* !ARCADECORE_HPP_ */