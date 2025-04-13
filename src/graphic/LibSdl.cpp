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
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
    window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SET_COLOR(renderer, COLORS[BLACK]);
}

Sdl::~Sdl()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

event_t Sdl::getEvent()
{
    event_t event;
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent)) {
        if (sdlEvent.type == SDL_KEYDOWN &&
            EVENT_TYPES.contains(sdlEvent.key.keysym.sym)){
            event.events.push_back(EVENT_TYPES.at(sdlEvent.key.keysym.sym));
        }
        if (sdlEvent.type == SDL_MOUSEMOTION) {
            event.events.push_back(A_MOUSE_MOVE);
            event.mPos = {COORD_TO_PERCENT(sdlEvent.button.x), COORD_TO_PERCENT(sdlEvent.button.y)};
        }
        if (sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
            event.events.push_back(MOUSE_EVENT_LINK.at(sdlEvent.button.button));
            event.mPos = {COORD_TO_PERCENT(sdlEvent.button.x), COORD_TO_PERCENT(sdlEvent.button.y)};
        }
    }
    return event;
}


void Sdl::displayText(text_t text)
{
    TTF_Font *font = nullptr;
    SDL_Color textColors = {};
    SDL_Surface *surface = nullptr;
    SDL_Rect posText = {};
    SDL_Texture *texture = nullptr;

    font = TTF_OpenFont(text.fontPath.c_str(), text.fontSize);
    if (!font)
        return;
    textColors = {text.color.r, text.color.g, text.color.b, 255};
    surface = TTF_RenderText_Blended(font, text.value.c_str(), textColors);
    if (!surface) {
        TTF_CloseFont(font);
        return;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    posText = {
        PERCENT_TO_COORD(text.pos.x),
        PERCENT_TO_COORD(text.pos.y),
        surface->w,
        surface->h
    };
    SDL_RenderCopy(renderer, texture, nullptr, &posText);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void Sdl::displaySprites(entity_t entity)
{
    SDL_Texture *texture = IMG_LoadTexture(renderer, entity.asset.c_str());
    SDL_Rect rect = CREATE_RECT(entity);

    if (texture) {
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
    } else {
        SET_COLOR(renderer, entity.color);
        printf("r = %d g = %d  b = %d a = %d\n", entity.color.r, entity.color.g, entity.color.b, entity.color.a);
        SDL_RenderFillRect(renderer, &rect);
        SET_COLOR(renderer, COLORS[BLACK]);
    }
}

void Sdl::display(data_t data)
{
    SET_COLOR(renderer, COLORS[BLACK]);
    SDL_RenderClear(renderer);

    for (const auto &entity : data.bg) {
        displaySprites(entity);
    }
    for (const auto &entity : data.objects) {
        displaySprites(entity);
    }
    for (const auto &entity : data.ui) {
        displaySprites(entity);
    }
    for (const auto &text : data.texts) {
        displayText(text);
    }
    SDL_RenderPresent(renderer);
}

extern "C" arcade::IGraphic* makeGraphic()
{
    return new Sdl();
}
