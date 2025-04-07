/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** ArcadeCore
*/

#include "ArcadeCore.hpp"
#include "DLLoaderGame.hpp"
#include "DLLoaderGraphic.hpp"
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
        DLLoaderGame<IGame> menu_loader(libPath);
        this->game_.reset(menu_loader.getInstance());
        run(); 
    }
    if (!libPath.empty() && type == GRAPHIC_LIB) {
        DLLoaderGraphic<IGraphic> loader(libPath);
        this->graphic_.reset(loader.getInstance());
        run();
    }
}

size_t handleMenu(event_e event, size_t libIndex, int lastGame)
{
    if (event == A_KEY_AUP)
        libIndex -= 1;
    if (event == A_KEY_ADOWN)
        libIndex += 1;
    if (libIndex < 2)
        libIndex = lastGame;
    if (libIndex > lastGame)
        libIndex = 0;
    return libIndex;
}

size_t indexOfCurrentLib(const std::string currentLib, const std::vector<std::string> allgraphics)
{
    for (size_t i = 0; i < allgraphics.size(); ++i) {
        if (allgraphics[i] == currentLib) {
            return i;
        }
    }
    return -1;
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
                graphicIndex = graphicIndex + 1;
                if (graphicIndex > allgraphics_.size() - 1)
                    graphicIndex = 0;
                break;
            }
            if (data.isMenu == true) {
                gameIndex = handleMenu(event, gameIndex, allgames_.size() - 1);
            }
            if (event == A_KEY_ENTER && data.isMenu == true) {
                game_.reset();
                break;
            }
        }
        if (graphic_ && game_) {
            graphic_->display(data);
            game_->handleEvent(instructions);
        } else if (!graphic_) {
            return load(allgraphics_[graphicIndex], GRAPHIC_LIB);
        } else {
            return load(allgames_[gameIndex], GAME_LIB);
        }
    }
}

std::vector<std::string> getAllGames()
{
    std::vector<std::string> games;
    void *handle;
    void *sym;

    for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
        handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!handle)
            continue;
        sym = dlsym(handle, "makeGame");
        if (!sym)
            continue;
        games.push_back(entry.path().c_str());
        dlclose(handle);
    }
    return games;
}

std::vector<std::string> getAllGraphics()
{
    std::vector<std::string> graphics;
    void *handle;
    void *sym;

    for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
        handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!handle)
            continue;
        sym = dlsym(handle, "makeGraphic");
        if (!sym)
            continue;
        graphics.push_back(entry.path().c_str());
        dlclose(handle);
    }
    return graphics;
}

arcade::ArcadeCore::ArcadeCore(int argc, const char *argv[])
{
    if (argc != NB_ARGS)
        throw Error("Error: Wrong number of arguments, we need the graphic lib and nothing else.");
    
    std::string libPath = argv[LIB_PATH_ARG];
    if (libPath.size() <= 3 || !endsWith(libPath, ".so"))
        throw Error("Error: Invalid library format, expected a .so file.");
    
    currentLib = libPath;
    allgames_ = getAllGames();
    allgraphics_ = getAllGraphics();

    DLLoaderGraphic<IGraphic> loader(currentLib);
    graphic_.reset(loader.getInstance());

    DLLoaderGame<IGame> menu_loader(MENU_PATH);
    game_.reset(menu_loader.getInstance());
    gameIndex = 0;
    graphicIndex = indexOfCurrentLib(currentLib, allgraphics_);
    run();
}
