#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SQUARE_SIZE = 50;

int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("Moving Square",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Set up the square
    SDL_Rect square;
    square.x = SCREEN_WIDTH / 2 - SQUARE_SIZE / 2;
    square.y = SCREEN_HEIGHT / 2 - SQUARE_SIZE / 2;
    square.w = SQUARE_SIZE;
    square.h = SQUARE_SIZE;

    // Set up the timer
    Uint32 prev_time = SDL_GetTicks();
    Uint32 curr_time;
    float delta_time;

    // Main loop
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Update the square's position
        curr_time = SDL_GetTicks();
        delta_time = (curr_time - prev_time) / 1000.0f;  // Convert to seconds
        prev_time = curr_time;

        square.x += (int)(100 * delta_time);  // Move 100 pixels per second

        // Draw the square
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &square);
        SDL_RenderPresent(renderer);

        // Wait a bit to control the frame rate
        SDL_Delay(10);
    }

    // Clean up and exit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}