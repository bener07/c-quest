#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int SQUARE_SIZE = 32;
const int Character_Rendering_XPosition = 0;
const int Character_Rendering_YPosition = 0;
const int CROP_RECT_WIDTH = 16;
const int CROP_RECT_HEIGHT = 16;

int main() {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("SDL Image Cropping", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Failed to create window: %s\n", SDL_GetError());
        return -1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("Failed to initialize SDL_image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    // Load the image
    SDL_Surface* imageSurface = IMG_Load("hero1.png");
    if (imageSurface == NULL) {
        printf("Failed to load image: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        return -1;
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
        return -1;
    }

    // Set the rectangle to crop from the image
    SDL_Rect cropRect;
    cropRect.x = Character_Rendering_XPosition;
    cropRect.y = Character_Rendering_YPosition;
    cropRect.w = CROP_RECT_WIDTH;
    cropRect.h = CROP_RECT_HEIGHT;

    // Calculate the scale factor to fit the cropped image into the square
    double scaleFactor = (double)SQUARE_SIZE / CROP_RECT_WIDTH;

    // Calculate the scaled dimensions of the cropped image
    int scaledWidth = CROP_RECT_WIDTH * scaleFactor;
    int scaledHeight = CROP_RECT_HEIGHT * scaleFactor;

    // Calculate the position of the scaled image within the square
    int squareX = (WINDOW_WIDTH - SQUARE_SIZE) / 2;
    int squareY = (WINDOW_HEIGHT - SQUARE_SIZE) / 2;

    // Calculate the position of the scaled image within the square
    int imageX = squareX + (SQUARE_SIZE - scaledWidth) / 2;
    int imageY = squareY + (SQUARE_SIZE - scaledHeight) / 2;

    // Render the scaled cropped image to the renderer
    SDL_Rect destRect;
    destRect.x = imageX;
    destRect.y = imageY;
    destRect.w = scaledWidth;
    destRect.h = scaledHeight;
    SDL_RenderCopyEx(renderer, imageTexture, &cropRect, &destRect, 0, NULL, SDL_FLIP_NONE);

    // Render to the screen
    SDL_RenderPresent(renderer);

    // Wait for user to quit
    SDL_Event event;
    while (SDL_WaitEvent(&event)) {
        if (event.type == SDL_QUIT) {
            break;
        }
    }

    // Clean up resources
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
