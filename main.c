#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "objects.h"


int QUIT = 0;
int FRAME_DELAY = 0;
#define TILE_SIZE 16
#define DESTINATION_SIZE 10

// main loop to handle the entire game
// it makes it easier to handle alterations
void gameLoop(){
    srand(time(NULL));
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
    srand(time(NULL));
    // SDL_Renderer *MapRenderer = SDL_CreateRenderer(window, 0,SDL_RENDERER_ACCELERATED);

    // include libraries after creating the renderer
    // #include "objects.h"
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
    Objeto wall;
    initMapObject(&wall, "Wall", "imagens/wall.png");
    Objeto floor;
    initMapObject(&floor, "Floor", "imagens/floor.png");
    // Load the tile map from an image
    TileMap* tileMap = loadTileMap("room 16 line.png");
    Painel helloPanel;
    SDL_Color panelColor = {255, 255, 255};
    createPanel(&helloPanel,
                "Sans_Pro/SourceSansPro-Regular.ttf",
                20,
                "Find the bug and recover all maps!",
                "Hello panel",
                windowWidth/2,
                windowHeight/2,
                300,
                200,
                windowWidth-300,
                0,
                300,
                30,
                panelColor
    );

    // Set the rectangle to crop from the image
    // this will control which caracter to be rendered
    Personagem Idle;
    Personagem Enemy1;
    Objeto paper1;
    Objeto paper2;
    Objeto paper3;
    Objeto paper4;
    Objeto key;
    // it's Idle
    initObject(&paper1, "Paper1", -220, -140, "imagens/paper.png");
    initObject(&paper2, "Paper2", -120, 170, "imagens/paper.png");
    initObject(&paper3, "Paper3", 100, 100, "imagens/paper.png");
    initObject(&paper4, "Paper4", 220, -20, "imagens/paper.png");
    initObject(&key, "Key", 340, -130, "imagens/key.png");
    initCharacter(
                    "Idle",
                    "imagens/hero1 32.png",
                    &Idle,
                    renderer,
                    -320,
                    -40,
                    32,
                    32,
                    32,
                    5
                    );
    initCharacter(
                    "Enemy 1",
                    "imagens/enemy 32.png",
                    &Enemy1,
                    renderer,
                    -10,
                    0,
                    32,
                    32,
                    32,
                    10
                    );
    // Wait for the user to close the window
    while (!QUIT) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    QUIT = !QUIT;
                    break;
                case SDL_KEYDOWN:
                    characterMovement(&Idle, tileMap, event);
                    break;
                default:
                    ImagePositionZero(&Idle);
                    break;
            }
        }
        // this functions need to be called first in order to render the character
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        // Render the tile map and the rest of the game
        renderTileMap(renderer, tileMap, floor.imageTexture, wall.imageTexture);
        renderCharacter(&Idle);
        renderCharacter(&Enemy1);
        renderObject(&key);
        renderObject(&paper1);
        renderObject(&paper2);
        renderObject(&paper3);
        renderObject(&paper4);
        checkCollision(&Idle, &paper1);
        checkCollision(&Idle, &paper2);
        checkCollision(&Idle, &paper3);
        checkCollision(&Idle, &paper4);
        keyCollision(&Idle, &key);
        renderPanel(&helloPanel);
        characterPanel(&Idle);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    for (int y = 0; y < tileMap->height; y++) {
        free(tileMap->tiles[y]);
    }
    // free(Idle);
    // free(floor);
    // free(wall);
    // DestroyPanel(&helloWorld);
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