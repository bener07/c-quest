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
                                          0);
    TTF_Init();
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // renderer variable where you write all the forms and vectors
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // SDL_Renderer *MapRenderer = SDL_CreateRenderer(window, 0,SDL_RENDERER_ACCELERATED);

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
    // Painel helloWorld;
    // SDL_Color panelColor = {255, 255, 255};
    // createPanel(&helloWorld,
    //             "Sans_Pro/SourceSansPro-Regular.ttf",
    //             24,
    //             "Hello world!",
    //             "Hello panel",
    //             0,
    //             0,
    //             200,
    //             200,
    //             20,
    //             20,
    //             100,
    //             100,
    //             panelColor
    // );

    // Set the rectangle to crop from the image
    // this will control which caracter to be rendered
    // Personagem Idle;
    // Objeto Room;

    // Load the floor and wall textures
    SDL_Surface* floorSurface = IMG_Load("imagens/floor.png");
    if (!floorSurface) {
        printf("Failed to load floor image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* floorTexture = SDL_CreateTextureFromSurface(renderer, floorSurface);
    SDL_FreeSurface(floorSurface);

    SDL_Surface* wallSurface = IMG_Load("imagens/wall.png");
    if (!wallSurface) {
        printf("Failed to load wall image: %s\n", IMG_GetError());
        SDL_DestroyTexture(floorTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* wallTexture = SDL_CreateTextureFromSurface(renderer, wallSurface);
    SDL_FreeSurface(wallSurface);

    // Load the tile map from an image
    TileMap* tileMap = loadTileMap("room 16 line.png");
    if (!tileMap) {
        SDL_DestroyTexture(wallTexture);
        SDL_DestroyTexture(floorTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // it's a room
    // initObject(&Room,
    //             "Room 2",
    //             0,
    //             0,
    //             "room 16 line.png");
    // it's Idle
    // initCharacter(
    //                 "Idle",
    //                 "imagens/hero1 32.png",
    //                 &Idle,
    //                 renderer,
    //                 0,
    //                 0,
    //                 32,
    //                 32,
    //                 32,
    //                 5
    //                 );
    // Clear the renderer
    SDL_RenderClear(renderer);
    // SDL_RenderClear(MapRenderer);

    // Wait for the user to close the window
    while (!QUIT) {
        SDL_RenderClear(renderer);
        // SDL_RenderClear(MapRenderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    QUIT = !QUIT;
                    break;
                case SDL_KEYDOWN:
                    // characterMovement(&Idle, &main, event);
                    break;
                default:
                    // ImagePositionZero(&Idle);
                    break;
            }
        }
        renderTileMap(renderer, main.map, floor.imageTexture, wall.imageTexture);
        SDL_RenderPresent(renderer);
        // SDL_RenderPresent(renderer);
        // renderCharacter(&Idle);
        // renderGameObject(&Room);
        // renderGameObject(&Room3);
        // renderPanel(&helloWorld);

        // Update the screen
    }

    for (int y = 0; y < main.map->height; y++) {
        free(main.map->tiles[y]);
    }
    // DestroyPanel(&helloWorld);
    SDL_DestroyRenderer(renderer);
    // SDL_DestroyRenderer(MapRenderer);
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