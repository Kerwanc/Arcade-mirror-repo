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
    set_escdelay(0);
    start_color();
    curs_set(0);
    win = newwin(LINES, COLS, 0, 0);
    keypad(win, TRUE);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
    nodelay(win, TRUE);
}

GraphicSample::~GraphicSample()
{
    delwin(win);
    endwin();
}

event_t GraphicSample::getEvent()
{
    event_t event;
    MEVENT mouse;
    int ch = wgetch(win);

    if (ch == ERR)
        return event;
    for (const auto &key: KEYBOARD_EVENT_LINK) {
        if (ch == key.second) {
            event.events.push_back(key.first);
        }

    }
    if (ch == KEY_MOUSE) {
        getmouse(&mouse);
        if (mouse.bstate & BUTTON1_PRESSED) {
            event.events.push_back(A_MOUSE_LEFT);
            event.mPos.x = (double)mouse.x;
            event.mPos.y = (double)mouse.y;
        }
        if (mouse.bstate & BUTTON3_PRESSED) {
            event.events.push_back(A_MOUSE_RIGHT);
            event.mPos.x = (double)mouse.x;
            event.mPos.y = (double)mouse.y;
        }
    }
    return event;
}

void GraphicSample::displayEntities(const std::vector<entity_t>& entities, short& pairID, short& colorID)
{
    for (const auto& entity : entities) {
        init_color(colorID,
                   entity.color.r * 1000 / 255,
                   entity.color.g * 1000 / 255,
                   entity.color.b * 1000 / 255);

        if (entity.character == ' ') {
            init_pair(pairID, colorID, colorID);
        } else {
            init_pair(pairID, colorID, COLOR_BLACK);
        }
        wattron(win, COLOR_PAIR(pairID));
        mvwaddch(win, entity.pos.y, entity.pos.x, entity.character);
        wattroff(win, COLOR_PAIR(pairID));
        colorID++;
        pairID++;
    }
}

void GraphicSample::displayTexts(const std::vector<text_t>& texts, short& pairID, short& colorID)
{
    for (const auto& text : texts) {
        init_color(colorID,
                   text.color.r * 1000 / 255,
                   text.color.g * 1000 / 255,
                   text.color.b * 1000 / 255);
        init_pair(pairID, colorID, COLOR_BLACK);
        wattron(win, COLOR_PAIR(pairID));
        mvwprintw(win, text.pos.y, text.pos.x, "%s", text.value.c_str());
        wattroff(win, COLOR_PAIR(pairID));
        colorID++;
        pairID++;
    }
}

void GraphicSample::display(data_t data)
{
    short pairID = 10;
    short colorID = 11;

    wclear(win);
    displayEntities(data.bg, pairID, colorID);
    displayEntities(data.objects, pairID, colorID);
    displayEntities(data.ui, pairID, colorID);
    displayTexts(data.texts, pairID, colorID);
    wrefresh(win);
}


extern "C" arcade::IGraphic* makeGraphic()
{
    return new GraphicSample();
}
