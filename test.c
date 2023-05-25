#include <stdio.h>
#include <stdlib.h>
#include <gif_lib.h>
#include <SDL2/SDL.h>

#define CHARACTER_WIDTH 16
#define CHARACTER_HEIGHT 16

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Character Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Open the GIF file using giflib
    GifFileType* gifFile = DGifOpenFileName("idle_down.gif", NULL);
    if (!gifFile) {
        printf("Failed to open GIF file\n");
        return 1;
    }

    // Read the GIF file
    int errorCode;
    if ((errorCode = DGifSlurp(gifFile)) != GIF_OK) {
        printf("Failed to read GIF file: %d\n", errorCode);
        DGifCloseFile(gifFile, NULL);
        return 1;
    }

    // Get the number of frames in the animation
    int frameCount = gifFile->ImageCount;
    int currentFrame = 0;

    // Create a texture to hold the character frames
    SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, CHARACTER_WIDTH, CHARACTER_HEIGHT);
    if (!texture) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        DGifCloseFile(gifFile, NULL);
        return 1;
    }

    // Main loop
    SDL_Event event;
    int quit = 0;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Clear the renderer
        SDL_RenderClear(renderer);

        // Get the current frame's image
        GifImageDesc* imageDesc = &gifFile->SavedImages[currentFrame].ImageDesc;
        GifByteType* imageData = gifFile->SavedImages[currentFrame].RasterBits;

        // Lock the texture for writing
        void* texturePixels;
        int texturePitch;
        SDL_LockTexture(texture, NULL, &texturePixels, &texturePitch);

        // Copy the character data to the texture
        for (int y = 0; y < CHARACTER_HEIGHT; y++) {
            for (int x = 0; x < CHARACTER_WIDTH; x++) {
                // Calculate the index of the current pixel in the GIF data
                int gifIndex = y * CHARACTER_WIDTH + x;
                // Calculate the index of the current pixel in the texture data
                int textureIndex = y * texturePitch + x * sizeof(uint32_t);
                // Copy the pixel data from the GIF to the texture
                ((uint32_t*)texturePixels)[textureIndex / sizeof(uint32_t)] = imageData[gifIndex];
            }
        }

        // Unlock the texture
        SDL_UnlockTexture(texture);

        // Render the texture
        SDL_RenderCopy(renderer, texture, NULL, NULL);

        // Update the renderer
        SDL_RenderPresent(renderer);

        // Delay between frames (adjust this to control the animation speed)
        SDL_Delay(100);

        // Move to the next frame
        currentFrame++;
        if (currentFrame >= frameCount) {
            currentFrame = 0;
        }
    }

    // Clean up the GIF file
    DGifCloseFile(gifFile, NULL);

    // Clean up SDL
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
