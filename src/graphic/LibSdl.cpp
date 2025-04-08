/*
** EPITECH PROJECT, 2025
** B-OOP-400-PAR-4-1-arcade-luigi.gomes
** File description:
** Sdl
*/

#include "LibSdl.hpp"
#include <SDL2/SDL.h>

Sdl::Sdl()
{
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

Sdl::~Sdl()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

event_t Sdl::getEvent()
{
    event_t event;
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_KEYDOWN) {
            switch (sdlEvent.key.keysym.sym) {
                case SDLK_ESCAPE:
                    event.events.push_back(A_KEY_ESC);
                    break;
                case SDLK_a:
                    event.events.push_back(A_KEY_A);
                    break;
                case SDLK_b:
                    event.events.push_back(A_KEY_B);
                    break;
                case SDLK_UP:
                    event.events.push_back(A_KEY_UP);
                    break;
                case SDLK_DOWN:
                    event.events.push_back(A_KEY_DOWN);
                    break;
                case SDLK_LEFT:
                    event.events.push_back(A_KEY_LEFT);
                    break;
                case SDLK_RIGHT:
                    event.events.push_back(A_KEY_RIGHT);
                    break;
                default:
                    break;
            }
        }
    }
    return event;
}

void Sdl::display(data_t data)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (const auto &entity : data.bg) {
        SDL_Texture *texture = IMG_LoadTexture(renderer, entity.asset.c_str());
        if (texture) {
            SDL_Rect rect = {(int)entity.pos.x, (int)entity.pos.y, (int)entity.size.x, (int)entity.size.y};
            SDL_RenderCopy(renderer, texture, nullptr, &rect);
        }
    }
    for (const auto &entity : data.objects) {
    }

    for (const auto &entity : data.ui) {
    }

    for (const auto &text : data.texts) {
    }

    SDL_RenderPresent(renderer);
}

extern "C" arcade::IGraphic* makeGraphic()
{
    return new Sdl();
}
