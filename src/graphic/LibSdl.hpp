/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** Sdl
*/

#ifndef SDL_HPP_
    #define SDL_HPP_
    #include <map>
    #include <iostream>
    #include <unordered_map>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include "IGraphic.hpp"

    const size_t WINDOW_SIZE = 1000;

    #define PERCENT_TO_COORD(pos) (int)((int)pos * ((int)WINDOW_SIZE / 100))
    #define COORD_TO_PERCENT(pos) (double)(((double)pos / (double)WINDOW_SIZE) * 100)

    #define SET_COLOR(rederer, color) void(SDL_SetRenderDrawColor(renderer,\
        color.r, color.g, color.b, color.a))
    #define CREATE_RECT(entity) SDL_Rect( \
        {PERCENT_TO_COORD(entity.pos.x), PERCENT_TO_COORD(entity.pos.y), \
        PERCENT_TO_COORD(entity.size.x), PERCENT_TO_COORD(entity.size.y)})

class Sdl : public arcade::IGraphic {
    public:
        Sdl();
        ~Sdl();
        event_t getEvent(void) override;
        void display(data_t data) override;
        void displayText(text_t text);
        void displaySprites(entity_t entity);

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};


static const std::map<SDL_Keycode, event_e> EVENT_TYPES =
{
    {SDLK_ESCAPE, A_KEY_ESC},
    {SDLK_SPACE, A_KEY_SPACE},
    {SDLK_DELETE, A_KEY_DEL},
    {SDLK_RETURN, A_KEY_ENTER},
    {SDLK_TAB, A_KEY_TAB},
    {SDLK_LCTRL, A_KEY_CTRL},
    {SDLK_RCTRL, A_KEY_CTRL},
    {SDLK_LSHIFT, A_KEY_SHIFT},
    {SDLK_RSHIFT, A_KEY_SHIFT},
    {SDLK_LALT, A_KEY_ALT},
    {SDLK_RALT, A_KEY_ALT},
    {SDLK_UP, A_KEY_UP},
    {SDLK_DOWN, A_KEY_DOWN},
    {SDLK_LEFT, A_KEY_LEFT},
    {SDLK_RIGHT, A_KEY_RIGHT},
    {SDLK_a, A_KEY_A},
    {SDLK_b, A_KEY_B},
    {SDLK_c, A_KEY_C},
    {SDLK_d, A_KEY_D},
    {SDLK_e, A_KEY_E},
    {SDLK_f, A_KEY_F},
    {SDLK_g, A_KEY_G},
    {SDLK_h, A_KEY_H},
    {SDLK_i, A_KEY_I},
    {SDLK_j, A_KEY_J},
    {SDLK_k, A_KEY_K},
    {SDLK_l, A_KEY_L},
    {SDLK_m, A_KEY_M},
    {SDLK_n, A_KEY_N},
    {SDLK_o, A_KEY_O},
    {SDLK_p, A_KEY_P},
    {SDLK_q, A_KEY_Q},
    {SDLK_r, A_KEY_R},
    {SDLK_s, A_KEY_S},
    {SDLK_t, A_KEY_T},
    {SDLK_u, A_KEY_U},
    {SDLK_v, A_KEY_V},
    {SDLK_w, A_KEY_W},
    {SDLK_x, A_KEY_X},
    {SDLK_y, A_KEY_Y},
    {SDLK_z, A_KEY_Z},
    {SDLK_0, A_KEY_0},
    {SDLK_1, A_KEY_1},
    {SDLK_2, A_KEY_2},
    {SDLK_3, A_KEY_3},
    {SDLK_4, A_KEY_4},
    {SDLK_5, A_KEY_5},
    {SDLK_6, A_KEY_6},
    {SDLK_7, A_KEY_7},
    {SDLK_8, A_KEY_8},
    {SDLK_9, A_KEY_9},
    {SDLK_F1, A_KEY_F1},
    {SDLK_F2, A_KEY_F2},
    {SDLK_F3, A_KEY_F3},
    {SDLK_F4, A_KEY_F4},
    {SDLK_F5, A_KEY_F5},
    {SDLK_F6, A_KEY_F6},
    {SDLK_F7, A_KEY_F7},
    {SDLK_F8, A_KEY_F8},
    {SDLK_F9, A_KEY_F9},
    {SDLK_F10, A_KEY_F10},
    {SDLK_F11, A_KEY_F11},
    {SDLK_F12, A_KEY_F12},
    {SDLK_KP_0, A_KEY_0},
    {SDLK_KP_1, A_KEY_1},
};

enum color_e {
    WHITE,
    BLACK,
    RED,
    GREEN,
    YELLOW
};

const color_t COLORS[] {
    {255, 255, 255, 255},
    {0, 0, 0, 255},
    {255, 0, 0, 255},
    {0, 255, 0, 255},
    {255, 255, 0, 255}
};

const std::map<Uint32, event_e> MOUSE_EVENT_LINK =
{
    {SDL_BUTTON_RIGHT, A_MOUSE_LEFT},
    {SDL_BUTTON_LEFT, A_MOUSE_RIGHT},
};

extern "C" arcade::IGraphic* makeGraphic();

#endif /* !SDL_HPP_ */


