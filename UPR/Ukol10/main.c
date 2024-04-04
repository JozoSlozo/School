#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "dynamic_array.h"

const int windowW = 1280;
const int windowH = 720;

int getRandomInRange(int min, int max){
    return rand() % max + min;
}

int initRect(SDL_Rect *rect, int x, int y){
    int random = getRandomInRange(50,150);
    rect->h = random;
    rect->w = random;
    rect->y = y - random/2;
    rect->x = x - random/2;
    return 0;
}

typedef struct {
    int rotation;
    int rotation_speed;
    int speed;
    SDL_Rect destination;
}snowflake;

int main()
{  
    SDL_Context context = sdl_context_init("snowflake", windowW, windowH);
    
    SDL_Event event;
    int running = 1;

    SDL_Texture *snowflake_texture = IMG_LoadTexture(context.renderer, "snowflake.png");
    dynarray snowflake_array;
    dynarray_init(&snowflake_array, 4);

    Uint64 last = SDL_GetPerformanceCounter();

    srand(time(NULL));

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
            if(event.type == SDL_MOUSEBUTTONDOWN){
                SDL_Rect rect;
                initRect(&rect, event.button.x, event.button.y);

                snowflake temp = {0, getRandomInRange(70,120), getRandomInRange(150,200), rect};
                snowflake *snow = malloc(sizeof(snowflake));
                *snow = temp;
                dynarray_push(&snowflake_array, snow);
            }
        }      
        SDL_RenderClear(context.renderer);

        for (int i = 0; i < snowflake_array.size; i++)
        {
            snowflake *temp = snowflake_array.items[i];
            SDL_RenderCopyEx(context.renderer, snowflake_texture, NULL, &temp->destination, temp->rotation, NULL, SDL_FLIP_NONE);
            
            temp->destination.y += temp->speed * deltaTime;
            temp->rotation += temp->rotation_speed * deltaTime;
            if (temp->destination.y > windowH)
            {
                dynarray_remove(&snowflake_array, temp);
            }
        }
        SDL_RenderPresent(context.renderer);

        last = now;
    }
    SDL_DestroyTexture(snowflake_texture);
    sdl_context_free(&context);
    dynarray_free(&snowflake_array);
    return 0;
}