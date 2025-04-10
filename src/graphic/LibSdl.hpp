/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** Sdl
*/

#ifndef SDL_HPP_
    #define SDL_HPP_
    
    #include <iostream>
    #include <unordered_map>
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>
    #include "IGraphic.hpp"

class Sdl : public arcade::IGraphic {
    public:
        Sdl();
        ~Sdl();
        event_t getEvent(void) override;
        void display(data_t data) override;
        void displayText(text_t text);

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
};

extern "C" arcade::IGraphic* makeGraphic();

#endif /* !SDL_HPP_ */


