#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define MAP_WIDTH 800
#define MAP_HEIGHT 600
#define TILE_SIZE 32

typedef enum {
    TILE_EMPTY,
    TILE_WALL,
    TILE_FLOOR,
    NUM_TILE_TYPES
} TileType;

TileType map[MAP_HEIGHT][MAP_WIDTH];

SDL_Texture* tileTextures[NUM_TILE_TYPES];

// Load tile textures
void loadTileTextures(SDL_Renderer* renderer) {
    // Load texture for TILE_WALL
    SDL_Surface* wallSurface = IMG_Load("imagens/wall.png");
    if (wallSurface == NULL) {
        printf("Failed to load wall image: %s\n", IMG_GetError());
        return;
    }
    tileTextures[TILE_WALL] = SDL_CreateTextureFromSurface(renderer, wallSurface);
    SDL_FreeSurface(wallSurface);

    // Load texture for TILE_FLOOR
    SDL_Surface* floorSurface = IMG_Load("imagens/floor.png");
    if (floorSurface == NULL) {
        printf("Failed to load floor image: %s\n", IMG_GetError());
        return;
    }
    tileTextures[TILE_FLOOR] = SDL_CreateTextureFromSurface(renderer, floorSurface);
    SDL_FreeSurface(floorSurface);

    // ... Load textures for other tile types if needed
}

// Load the map from an image
void loadMapFromImage(const char* filename) {
    SDL_Surface* mapSurface = IMG_Load(filename);
    if (mapSurface == NULL) {
        printf("Failed to load map image: %s\n", IMG_GetError());
        return;
    }

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            Uint32 pixel = ((Uint32*)mapSurface->pixels)[y * MAP_WIDTH + x];
            Uint8 r, g, b;
            SDL_GetRGB(pixel, mapSurface->format, &r, &g, &b);

            if (r == 255 && g == 255 && b == 255) {
                map[y][x] = TILE_WALL;
            } else {
                map[y][x] = TILE_FLOOR;
            }
        }
    }

    SDL_FreeSurface(mapSurface);
}

// Render the map
void renderMap(SDL_Renderer* renderer) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            TileType tile = map[y][x];

            SDL_Texture* texture = tileTextures[tile];

            if (texture != NULL) {
                SDL_Rect destRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
                SDL_RenderCopy(renderer, texture, NULL, &destRect);
            }
        }
    }
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Tile Map Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        return 1;
    }

    // Load the tile textures
    loadTileTextures(renderer);

    // Load the map from an image
    loadMapFromImage("imagens/room.png");

    // Game loop
    int quit = 0;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Render the map
        renderMap(renderer);

        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup tile textures
    for (int i = 0; i < NUM_TILE_TYPES; ++i) {
        SDL_DestroyTexture(tileTextures[i]);
    }

    // Cleanup SDL_image
    IMG_Quit();

    // Cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
