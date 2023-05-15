#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "funcionalidades/messages.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SQUARE_SIZE = 50;

int quit(SDL_Window* window, SDL_Renderer *renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
    return 0;
}

int main(int argc, char* argv[]){
    SDL_Window* window = SDL_CreateWindow("Simple Square",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    // renderer variable where you write all the forms and vectors
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect *square;
    createPanel(
                square,
                (SCREEN_WIDTH / 2 - SQUARE_SIZE /2),
                (SCREEN_HEIGHT / 2 - SQUARE_SIZE /2),
                SQUARE_SIZE, SQUARE_SIZE
    );
    // Wait for the user to close the window
    int SPEED = 1;
    SDL_Event event;
    while (1) {
        SDL_PollEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            quit(window, renderer);
            break;
        case SDL_KEYDOWN:
            // handles the key press with the Arrow keys
            switch(event.key.keysym.sym){
                case SDLK_UP:
                    square->y -= SPEED;
                    break;
                case SDLK_DOWN:
                    square->y += SPEED;
                    break;
                case SDLK_LEFT:
                    square->x -= SPEED;
                    break;
                case SDLK_RIGHT:
                    square->x += SPEED;
                    break;
            // CTRL increments the speed
                case SDLK_LCTRL:
                    SPEED += 10;
                    break;
            }
            break;
        }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, square);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
    }
    return 0;
}