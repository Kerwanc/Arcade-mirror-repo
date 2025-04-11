/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** GraphicSample
*/

#ifndef NCURSES
    #define NCURSES

    #include <ncurses.h> 
    #include <iostream>
    #include <map>
    #include <memory>
    #include "IGraphic.hpp"
    constexpr int KEY_PRESSED_ENTER = 10;
    constexpr int KEY_PRESSED_ESC = 27;
    constexpr int CONVERT_UINT = 1000 / 255;

class GraphicSample : public arcade::IGraphic {
    public:
        GraphicSample();
        ~GraphicSample();
        event_t getEvent(void) override;
        void display(data_t data) override;
        void displayTexts(const std::vector<text_t>& texts, short& pairID, short& colorID);
        void displayEntities(const std::vector<entity_t>& entities, short& pairID, short& colorID);

    private:
        WINDOW *win;
};

const std::map<event_e, int> KEYBOARD_EVENT_LINK =
{
    {A_KEY_A, 'a'},
    {A_KEY_ESC, KEY_PRESSED_ESC},
    {A_KEY_UP, KEY_UP},
    {A_KEY_LEFT, KEY_LEFT},
    {A_KEY_RIGHT, KEY_RIGHT},
    {A_KEY_DOWN, KEY_DOWN   },
    {A_KEY_ENTER, KEY_PRESSED_ENTER}
};

extern "C" arcade::IGraphic* makeGraphic();

#endif /* !NCURSES */
