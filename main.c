#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

int QUIT = 0;
int FRAME_DELAY = 0;

// main loop to handle the entire game
// it makes it easier to handle alterations
void gameLoop(){
    SDL_Window* window = SDL_CreateWindow("Character Movement",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          800, 600,
                                          SDL_WINDOW_FULLSCREEN_DESKTOP);
    TTF_Init();
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // renderer variable where you write all the forms and vectors
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // include libraries after creating the renderer
    #include "objects.h"
    #include "funcionalidades/general.h"
    #include "funcionalidades/eventos.h"


    // Initialize the images
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(0);
    }
    Painel helloWorld;
    SDL_Color panelColor = {255, 255, 255};
    createPanel(&helloWorld,
                "Sans_Pro/SourceSansPro-Regular.ttf",
                24,
                "Hello world!",
                "Hello panel",
                0,
                0,
                200,
                200,
                20,
                20,
                100,
                100,
                panelColor
    );

    // Set the rectangle to crop from the image
    // this will control which caracter to be rendered
    Personagem Idle;
    Objeto Room;
    // it's a room
    initObject(&Room,
                "Room 2",
                0,
                0,
                "imagens/room.png");
    // it's Idle
    initCharacter(
                    "Idle",
                    "imagens/hero1 32.png",
                    &Idle,
                    renderer,
                    0,
                    0,
                    32,
                    32,
                    32,
                    5
                    );
    // Clear the renderer
    SDL_RenderClear(renderer);

    // Wait for the user to close the window
    while (!QUIT) {
        SDL_RenderClear(renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    QUIT = !QUIT;
                    break;
                case SDL_KEYDOWN:
                    characterMovement(&Idle, &Room, event);
                    break;
                default:
                    ImagePositionZero(&Idle);
                    break;
            }
        }
        renderCharacter(&Idle);
        renderGameObject(&Room);
        // renderGameObject(&Room3);
        renderPanel(&helloWorld);

        // Update the screen
        SDL_RenderPresent(renderer);
    }


    DestroyPanel(&helloWorld);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    SDL_Quit();
    exit(0);
}



int main(int argc, char* argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    gameLoop();
    return 0;
}