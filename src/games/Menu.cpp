/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** Menu
*/

#include "Menu.hpp"

void Menu::setupBackground()
{
    menu.bg.push_back({{0, 0}, {100, 100}, 0, BG_ASSET, {0, 0, 0, 255}, UP});
}

void Menu::setupTitle(double& Pos)
{
    menu.texts.push_back({{45, Pos}, 20, "Arcade Menu:", ARCADE_FONT, {255, 255, 255, 255}});
    Pos += 5;
    menu.texts.push_back({{44, Pos}, 20, "Select Your Game !", ARCADE_FONT, {255, 255, 255, 255}});
}

void Menu::loadGames(double& Pos)
{
    void *sym;
    void *handle;

    for (const auto& entry : std::filesystem::directory_iterator("./lib")) {
        handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!handle)
            continue;
        sym = dlsym(handle, "makeGame");
        dlclose(handle);
        if (!sym)
            continue;
        Pos += 3;
        menu.texts.push_back({{44.5, Pos}, 12, entry.path().filename().string(), ARCADE_FONT, {200, 200, 200, 255}});
    }
}

void Menu::setupGraphicTitle(double& Pos)
{
    Pos += 5;
    menu.texts.push_back({{44, Pos}, 20, "Select Your Graphic !", ARCADE_FONT, {255, 255, 255, 255}});
}

void Menu::loadGraphics(double& Pos)
{
    void *sym;
    void *handle;

    for (const auto& entry : std::filesystem::directory_iterator("./lib")) {
        handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!handle)
            continue;
        sym = dlsym(handle, "makeGraphic");
        dlclose(handle);
        if (!sym)
            continue;
        Pos += 3;
        menu.texts.push_back({{44.5, Pos}, 12, entry.path().filename().string(), ARCADE_FONT, {200, 200, 200, 255}});
    }
}

Menu::Menu()
{
    double Pos = 40;

    setupBackground();
    setupTitle(Pos);
    loadGames(Pos);
    nbGames = menu.texts.size() - 1;

    setupGraphicTitle(Pos);
    loadGraphics(Pos);
    nbGraphics = menu.texts.size() - 1;

    selectedIndex = 2;
}

Menu::~Menu()
{
}

data_t Menu::update(void)
{
    for (size_t i = 2; i != menu.texts.size(); i++) {
        if (i == selectedIndex) {
            menu.texts[i].color = {255, 000, 000, 255};
        }
        if (i != selectedIndex) {
            menu.texts[i].color = {200, 200, 200, 255};
        }
    }
    return menu;
}

std::string addLibPrefix(const std::string filename)
{
    return "./lib/" + filename;
}

void Menu::handleEvent(event_t CurrentEvent)
{
    static size_t currentIndex = nbGames;
    static size_t minIndex = 2;

    for (const auto &event: CurrentEvent.events) {
        if (event == A_KEY_UP)
                selectedIndex -= 1;
        if (event == A_KEY_DOWN)
                selectedIndex += 1;
        if (event == A_KEY_ENTER) {
            if (currentIndex == nbGames)
                newlibs.game = addLibPrefix(menu.texts[selectedIndex].value);
            if (currentIndex == nbGraphics) {
                newlibs.graphic = addLibPrefix(menu.texts[selectedIndex].value);
                menu.libs = newlibs;
                currentIndex = nbGames;
                minIndex = 2;
                selectedIndex = 2;
                break;
            }
            currentIndex = nbGraphics;
            minIndex = nbGames + 2;
            selectedIndex = minIndex;
        }
    }
    if (selectedIndex < minIndex)
        selectedIndex = currentIndex;
    if (selectedIndex > currentIndex)
        selectedIndex = minIndex;
}

extern "C" arcade::IGame* makeGame() {
    return new Menu();
}
