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
    TTF_Init();
    window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 1000, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
}

Sdl::~Sdl()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
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
                case SDLK_RETURN:
                    event.events.push_back(A_KEY_ENTER);
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
        SDL_DestroyTexture(texture);
    }
    for (const auto &entity : data.objects) {
    }

    for (const auto &entity : data.ui) {
    }
    for (const auto &text : data.texts) {
        TTF_Font *font = TTF_OpenFont(text.fontPath.c_str(), text.fontSize);
        if (!font)
            continue;
        SDL_Color sdlColor = {text.color.r, text.color.g, text.color.b, 255};
        SDL_Surface *surface = TTF_RenderText_Blended(font, text.value.c_str(), sdlColor);
        if (!surface) {
            TTF_CloseFont(font);
            continue;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect destRect = {
            static_cast<int>(text.pos.x * 1000 / 100),
            static_cast<int>(text.pos.y * 1000 / 100),
            surface->w,
            surface->h
        };
        SDL_RenderCopy(renderer, texture, nullptr, &destRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
        TTF_CloseFont(font);
    }
    SDL_RenderPresent(renderer);
}

extern "C" arcade::IGraphic* makeGraphic()
{
    return new Sdl();
}
