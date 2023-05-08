#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char** argv) {

    // Declaration
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning = true;

    // Initialisation
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Unable to init SDL : %s", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow("MyWindow", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL) {
        printf("Unable to create window : %s", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL) {
        printf("Unable to create renderer : %s", SDL_GetError());
        return 1;
    }

    // Infinite loop
    while(isRunning) {

        SDL_Event event;

        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear screen
        SDL_RenderClear(renderer);

        // render code goes here.....

        // Render modification
        SDL_RenderPresent(renderer);
    }

    // Free
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return 0;
}
