#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 16

typedef enum {
    TILE_FLOOR,
    TILE_WALL
} TileType;

typedef struct {
    TileType** tiles;
    int width;
    int height;
} TileMap;



void renderTileMap(SDL_Renderer* renderer, TileMap* tileMap, SDL_Texture* floorTexture, SDL_Texture* wallTexture) {
    for (int y = 0; y < tileMap->height; y++) {
        for (int x = 0; x < tileMap->width; x++) {
            TileType tile = tileMap->tiles[y][x];
            SDL_Rect destRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            if (tile == TILE_WALL) {
                SDL_RenderCopy(renderer, wallTexture, NULL, &destRect);
            } else {
                SDL_RenderCopy(renderer, floorTexture, NULL, &destRect);
            }
        }
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Tile Map Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        return 1;
    }

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

    SDL_Event event;
    int quit = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the tile map
        renderTileMap(renderer, tileMap, floorTexture, wallTexture);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    for (int y = 0; y < tileMap->height; y++) {
        free(tileMap->tiles[y]);
    }
    free(tileMap->tiles);
    free(tileMap);

    SDL_DestroyTexture(wallTexture);
    SDL_DestroyTexture(floorTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
