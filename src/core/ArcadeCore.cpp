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

arcade::ArcadeCore::~ArcadeCore()
{
    game_.reset();
    graphic_.reset();
}

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
    }
    if (!libPath.empty() && type == GRAPHIC_LIB) {
        DLLoaderGraphic<IGraphic> loader(libPath);
        this->graphic_.reset(loader.getInstance());
    }
}

int indexOfCurrentLib(const std::string currentLib, const std::vector<std::string> allgraphics)
{
    for (int i = 0; i < (int)allgraphics.size(); i++) {
        if (allgraphics[i].substr(allgraphics[i].find("a"), allgraphics[i].npos) ==
            currentLib.substr(currentLib.find("a"), currentLib.npos)) {
            return i;
        }
    }
    return -1;
}


void arcade::ArcadeCore::switchGraphicLib()
{
    graphic_.reset();
    graphicIndex = graphicIndex + 1;
    if (graphicIndex > (int)allgraphics_.size() - 1)
        graphicIndex = 0;
}

void arcade::ArcadeCore::menuReloading(const data_t& data)
{
    game_.reset();
    graphic_.reset();
    load(data.libs.game, GAME_LIB);
    load(data.libs.graphic, GRAPHIC_LIB);
    return run();
}

void arcade::ArcadeCore::reloadLibs(void)
{
    if (!graphic_) {
        load(allgraphics_[graphicIndex], GRAPHIC_LIB);
        return run();
    } else if (!game_) {
        load(allgames_[gameIndex], GAME_LIB);
        return run();
    }
}

void arcade::ArcadeCore::run()
{
    event_t instructions;
    data_t data;
    data_t prevData = game_->update();

    graphic_->display(prevData);
    while (true) {
        instructions = graphic_->getEvent();
        game_->handleEvent(instructions);
        data = game_->update();
        graphic_->display(data);
        if (handleInstructions(instructions, prevData, data))
            return;
        reloadLibs();
        prevData = data;
    }
}

bool arcade::ArcadeCore::handleInstructions(const event_t& instructions, const data_t& prevData, const data_t& data)
{
    for (const auto& event : instructions.events) {
        if (event == A_KEY_ESC)
            return true;
        if (event == A_KEY_A)
            switchGraphicLib();
        if (prevData.libs.game != data.libs.game ||
            prevData.libs.graphic != data.libs.graphic) {
            menuReloading(data);
        }
    }
    return false;
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
    if (graphicIndex == -1)
        throw Error("Error: current lib isn't in lib directory");
    run();
}
