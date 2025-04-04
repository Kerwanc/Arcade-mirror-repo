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
    #include <memory>
    #include "IGraphic.hpp"

class GraphicSample : public arcade::IGraphic {
    public:
        GraphicSample();
        ~GraphicSample();
        event_t getEvent(void) override;
        void display(data_t data) override;

    private:
        WINDOW *win;
};

extern "C" arcade::IGraphic* loadingLib();

#endif /* !NCURSES */
