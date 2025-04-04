/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** ArcadeCore
*/

#include "ArcadeCore.hpp"
#include "DLLoader.hpp"
#include "Error.hpp"
#include "Ncurses.hpp"
#include "ICore.hpp"

bool endsWith(const std::string& src, const std::string& ending)
{
    size_t pos = src.size() - ending.size();
    size_t n = ending.size();

    return !src.compare(pos, n, ending);
}

void arcade::ArcadeCore::load(std::string libPath, typeLib_e type)
{
    if (!libPath.empty() && type == GAME_LIB) {
        DLLoader<IGame> menu_loader(libPath);
        this->game_.reset(menu_loader.getInstance());
    }
    if (!libPath.empty() && type == GRAPHIC_LIB) {
        DLLoader<IGraphic> loader(libPath);
        this->graphic_.reset(loader.getInstance());
        run();
    }
}

void arcade::ArcadeCore::run() 
{
    event_t instructions;
    data_t data;

    while (true) {
        data = game_->update();
        graphic_->display(data);
        instructions = graphic_->getEvent();
        for (const auto &event: instructions.events) {
            if (event == A_KEY_ESC) {
                game_.reset();
                graphic_.reset();
                return;
            }
            if (event == A_KEY_A) {
                graphic_.reset();
                break;
            }
        }
        if (graphic_) {
            graphic_->display(data);
            game_->handleEvent(instructions);
        } else {
            return load("./lib/arcade_ncurses.so", GRAPHIC_LIB);
        }
    }
}

arcade::ArcadeCore::ArcadeCore(int argc, const char *argv[])
{
    if (argc != NB_ARGS)
        throw Error("Error: Wrong number of arguments, we need the graphic lib and nothing else.");
    
    std::string libPath = argv[LIB_PATH_ARG];
    if (libPath.size() <= 3 || !endsWith(libPath, ".so"))
        throw Error("Error: Invalid library format, expected a .so file.");
    
    currentLib = libPath;
    DLLoader<IGraphic> loader(currentLib);
    graphic_.reset(loader.getInstance());

    DLLoader<IGame> menu_loader("./lib/arcade_menu.so");
    game_.reset(menu_loader.getInstance());
    
    run();
}
