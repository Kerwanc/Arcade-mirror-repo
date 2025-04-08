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
        case KEY_PRESSED_ESC:
            event.events.push_back(A_KEY_ESC);
            break;
        case 'a':
            event.events.push_back(A_KEY_A);
            break;
        case 'b':
            event.events.push_back(A_KEY_B);
            break;
        case KEY_UP:
            event.events.push_back(A_KEY_UP);
            break;
        case KEY_DOWN:
            event.events.push_back(A_KEY_DOWN);
            break;
        case KEY_LEFT:
            event.events.push_back(A_KEY_LEFT);
            break;
        case KEY_RIGHT:
            event.events.push_back(A_KEY_RIGHT);
            break;
        case KEY_PRESSED_ENTER:
            event.events.push_back(A_KEY_ENTER);
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
    for (const auto &entity: data.bg) {
        init_color(colorID, entity.color.r * 1000 / 255, entity.color.g * 1000 / 255, entity.color.b * 1000 / 255);
        init_pair(pairID, colorID, COLOR_BLACK);
        wattron(win, COLOR_PAIR(pairID));
        mvwaddch(win, entity.pos.x, entity.pos.y, entity.character);
        colorID += 1;
        pairID += 1;
    }
    for (const auto &entity : data.objects) {
        init_color(colorID, entity.color.r * 1000 / 255, entity.color.g * 1000 / 255, entity.color.b * 1000 / 255);
        init_pair(pairID, colorID, COLOR_BLACK);
        wattron(win, COLOR_PAIR(pairID));
        mvwaddch(win, entity.pos.x, entity.pos.y, entity.character);
        colorID += 1;
        pairID += 1;
    }
    for (const auto &entity : data.ui) {
        init_color(colorID, entity.color.r * 1000 / 255, entity.color.g * 1000 / 255, entity.color.b * 1000 / 255);
        init_pair(pairID, colorID, COLOR_BLACK);
        wattron(win, COLOR_PAIR(pairID));
        mvwaddch(win, entity.pos.x, entity.pos.y, entity.character);
        colorID += 1;
        pairID += 1;
    }
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

extern "C" arcade::IGraphic* makeGraphic()
{
    return new GraphicSample();
}
