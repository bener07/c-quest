#include <SDL2/SDL.h>
#include <stdio.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define OBJECT_SIZE 50

// Structure representing an object
typedef struct {
    int x;
    int y;
} Object;

// Function to check if a point is inside an object
int pointInsideObject(int x, int y, Object* object) {
    return (x >= object->x && x <= object->x + OBJECT_SIZE &&
            y >= object->y && y <= object->y + OBJECT_SIZE);
}

int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Object Selection", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (window == NULL) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return 1;
    }

    // Object
    Object object = { WINDOW_WIDTH / 2 - OBJECT_SIZE / 2, WINDOW_HEIGHT / 2 - OBJECT_SIZE / 2 };

    // Event loop
    SDL_Event event;
    int quit = 0;
    int objectExists = 1;
    while (!quit) {
        // Process events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                // Check if the left mouse button is pressed
                if (event.button.button == SDL_BUTTON_LEFT) {
                    // Get the mouse position
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;

                    // Check if the mouse click is inside the object
                    if (pointInsideObject(mouseX, mouseY, &object)) {
                        // Remove the object by setting objectExists to 0
                        objectExists = 0;
                    }
                }
            }
        }

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render the object if it exists
        if (objectExists) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_Rect objectRect = { object.x, object.y, OBJECT_SIZE, OBJECT_SIZE };
            SDL_RenderFillRect(renderer, &objectRect);
        }

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
