#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "objects.h"

int QUIT = 0;
int FRAME_DELAY = 500;

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
    #include "funcionalidades/general.h"
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize the images
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(0);
    }

    // load image character for IDle
    SDL_Surface* imageSurface = IMG_Load("hero1.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        exit(0);
    }
    // Create a texture from the image surface
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (imageTexture == NULL) {
        printf("Failed to create texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        exit(0);
    }

    // Set the rectangle to crop from the image
    // this will control which caracter to be rendered
    SDL_Rect Idle_Img_Rendering_Rect;
    SDL_Rect Idle_Dest_Rect;
    Personagem Idle;
    initCharacter(&Idle, renderer, imageTexture,&Idle_Img_Rendering_Rect, &Idle_Dest_Rect);
    // Clear the renderer
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, imageTexture, &Idle_Img_Rendering_Rect, NULL);

    // Wait for the user to close the window
    while (!QUIT) {
        handleEvents(&Idle);
        SDL_RenderClear(renderer);
        renderCharacter(&Idle);
        // Update the screen
        SDL_RenderPresent(renderer);
        SDL_Delay(FRAME_DELAY);
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