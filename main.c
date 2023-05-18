#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "funcionalidades/general.h"
#include "funcionalidades/eventos.h"


void gameLoop(){
    SDL_Window* window = SDL_CreateWindow("Simple Square",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    // renderer variable where you write all the forms and vectors
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Rect square;
    // Wait for the user to close the window
    while (!QUIT) {
        handleEvents();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the character
        createPanel(
                &square,
                characterX,
                characterY,
                SQUARE_SIZE, SQUARE_SIZE
        );
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &square);

        // Update the screen
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(0);
}



int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    gameLoop();
    return 0;
}