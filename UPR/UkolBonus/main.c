#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "sdl.h"
#include "dynamic_array.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int windowW = 1280;
const int windowH = 720;

//timer
Uint32 timeT = 1000;

Uint32 spawnMole(Uint32 T, void *param) {
    printf("Executing function every %d ms\n", timeT);
    return T;
}

int initTimer(SDL_TimerID *timer, SDL_Context context){

    *timer = SDL_AddTimer(timeT, spawnMole, NULL);

    if (!timer) {
        printf("SDL_AddTimer Error: %s\n", SDL_GetError());
        sdl_context_free(&context);
        TTF_Quit();
        return 1;
    }
}
int changeTimer(int newT, SDL_TimerID *timer, SDL_Context context){
    timeT = newT;
    SDL_RemoveTimer(*timer);
    initTimer(timer, context);
}

int emojiLocation(SDL_Rect *rect, int x, int y){
    rect->h = 200;
    rect->w = 200;
    rect->y = y;
    rect->x = x;
}

int main()
{  
    //init libs
    SDL_Context context = sdl_context_init("whack a mole", windowW, windowH);

    if (TTF_Init() != 0) {
        printf("TTF_Init Error: %s\n", TTF_GetError());
        sdl_context_free(&context);
        return 1;
    }
    //main inits
    SDL_Event event;
    int running = 1;

    //util inits
    Uint64 last = SDL_GetPerformanceCounter();

    SDL_TimerID timerID;
    initTimer(&timerID, context);

    SDL_Texture *mole_encyclopedia = IMG_LoadTexture(context.renderer, "emojipedia.jpg");

    while (running == 1)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        double deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
            }
        }      
        
        SDL_RenderClear(context.renderer);
        SDL_Rect srcRect;
        emojiLocation(&srcRect, 100, 100);
        SDL_Rect dstRect;
        emojiLocation(&dstRect, 200, 200);
        SDL_RenderCopy(context.renderer, mole_encyclopedia, &srcRect, &dstRect);
        SDL_RenderPresent(context.renderer);

        last = now;
    }
    SDL_RemoveTimer(timerID);
    sdl_context_free(&context);
    TTF_Quit();
    SDL_DestroyTexture(mole_encyclopedia);
    return 0;
}
