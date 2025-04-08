/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** Menu
*/

#include "Menu.hpp"

Menu::Menu()
{
    void *handle;
    void *sym;
    double Pos = 4;

    menu.bg.push_back({{0,0}, {1920,1080}, 0, "./assets/Arcade_background.png", {0,0,0, 255}, UP});
    menu.texts.push_back({{5, 2}, 20, "Arcade Menu:", "", {255, 255, 255, 255}});
    menu.texts.push_back({{18, 2}, 20, "Select Your Game !", "", {255, 255, 255, 255}});
    for (const auto &entry : std::filesystem::directory_iterator("./lib")) {
        handle = dlopen(entry.path().c_str(), RTLD_LAZY);
        if (!handle)
            continue;
        sym = dlsym(handle, "makeGame");
        if (!sym)
            continue;
        dlclose(handle);
        if (entry.is_regular_file() && entry.path().filename().string().find('.')) {
            menu.texts.push_back({{5, Pos}, 12, entry.path().filename().string(), "", {200, 200, 200, 255}});
            Pos += 1;
        }
    }
    menu.isMenu = true;
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

void Menu::handleEvent(event_t CurrentEvent)
{
    for (const auto &event: CurrentEvent.events) {
        if (event == A_KEY_UP) {
                selectedIndex -= 1;
        }
        if (event == A_KEY_DOWN) {
                selectedIndex += 1;
        }
    }
    if (selectedIndex < 2)
        selectedIndex = menu.texts.size() - 1;
    if (selectedIndex > menu.texts.size() - 1)
        selectedIndex = 2;
}

extern "C" arcade::IGame* makeGame() {
    return new Menu();
}
