#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

const int windowW = 1280;
const int windowH = 720;

int GetRandIntInRange(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

SDL_Rect CreateRandomRect(){
    SDL_Rect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = GetRandIntInRange(0+rect.w, windowW-rect.w);
    rect.y = GetRandIntInRange(0+rect.h, windowH-rect.h);
    return rect;
}
char* intToString(int value) {
    static char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d", value);
    return buffer;
}

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("SDL experiments", 0, 0, windowW, windowH, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


    SDL_Event event;
    int running = 1;

    Uint64 last = SDL_GetPerformanceCounter();

    //create amogus rectangles
    SDL_Texture *image = IMG_LoadTexture(renderer, "image.png");
    srand(time(NULL));
    SDL_Rect rectArr[4];
    for (int i = 0; i < 4; i++)
    {
        rectArr[i] = CreateRandomRect();
    }
    //create text 
    int points = 0;
    SDL_Color barva = {255,255,255,255};
    TTF_Font* font = TTF_OpenFont("arial.ttf", 100);
    SDL_Rect location;
    location.h = 100;
    location.w = 100;
    location.x = windowW/2 - location.w;
    location.y = 0;
    SDL_Surface* surface;
    SDL_Texture* texture;

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
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                int check = 0;
                SDL_Point point;
                point.x = event.button.x;
                point.y = event.button.y;
                for (int i = 0; i < 4; i++)
                {   
                    if (SDL_PointInRect(&point, &rectArr[i]))//check if cursor is in any amogus rectangle
                    {
                        rectArr[i] = CreateRandomRect();
                        points += 100;
                        check = 1;
                    }
                }
                if (check == 0)
                {
                    points -= 50;
                }
            }
        }         
        SDL_RenderClear(renderer);//background clear

        for (int i = 0; i < 4; i++)
        {
            SDL_RenderCopy(renderer, image, NULL, &rectArr[i]);//display amogus rectangle
        }
        
        surface = TTF_RenderText_Blended(font, intToString(points), barva);//update text surface
        texture = SDL_CreateTextureFromSurface(renderer, surface); // surface to texture
        SDL_RenderCopy(renderer, texture, NULL, &location); //display text 

        SDL_RenderPresent(renderer);// renderer update

        last = now;
    }
    SDL_DestroyTexture(image);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}