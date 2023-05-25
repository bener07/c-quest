#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "objects.h"
#include "funcionalidades/general.h"

// main loop to handle the entire game
// it makes it easier to handle alterations
void gameLoop(){
    SDL_Window* window = SDL_CreateWindow("Character Movement",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          0, 0,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    // renderer variable where you write all the forms and vectors
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    #include "funcionalidades/eventos.h"
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
                squareSize, squareSize
        );
     // Renderers
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