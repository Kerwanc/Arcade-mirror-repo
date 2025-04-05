/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** GraphicSample
*/

#include "Ncurses.hpp"

GraphicSample::GraphicSample()
{
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(0);
    win = newwin(LINES, COLS, 0, 0);
    keypad(win, TRUE);
    wbkgd(win, COLOR_BLACK);
}

GraphicSample::~GraphicSample()
{
    delwin(win);
    endwin();
}

event_t GraphicSample::getEvent()
{
    event_t event;
    int ch = wgetch(win);

    switch (ch) {
        case 27:
            event.events.push_back(A_KEY_ESC);
            break;
        case 'a':
            event.events.push_back(A_KEY_A);
            break;
        case 'b':
            event.events.push_back(A_KEY_B);
            break;
        case KEY_UP:
            event.events.push_back(A_KEY_AUP);
            break;
        case KEY_DOWN:
            event.events.push_back(A_KEY_ADOWN);
            break;
        case KEY_LEFT:
            event.events.push_back(A_KEY_ALEFT);
            break;
        case KEY_RIGHT:
            event.events.push_back(A_KEY_ARIGHT);
            break;
        default:
            break;
    }
    return event;
}

void GraphicSample::display(data_t data)
{
    short pairID = 10;
    short colorID = 11;

    wclear(win);
    for (const auto &entity : data.objects)
        mvwprintw(win, entity.pos.y, entity.pos.x, "*");
    for (const auto &entity : data.ui)
        mvwprintw(win, entity.pos.y, entity.pos.x, "@");
    for (const auto &text : data.texts) {
        init_color(colorID, text.color.r * 1000 / 255, text.color.g * 1000 / 255, text.color.b * 1000 / 255);
        init_pair(pairID, colorID, COLOR_BLACK);
        wattron(win, COLOR_PAIR(pairID));
        mvwprintw(win, text.pos.y, text.pos.x, "%s", text.value.c_str());
        wattroff(win, COLOR_PAIR(pairID));
        colorID += 1;
        pairID += 1;
    }
    wrefresh(win);
}

extern "C" arcade::IGraphic* loadingLib()
{
    return new GraphicSample();
}
