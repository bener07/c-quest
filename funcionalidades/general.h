#include <SDL2/SDL.h>
#include <stdlib.h>

// Creates a Panel and returns an Object as a renderer
// it's only to make it easier
int renderObject(SDL_Rect* Object, int x_pos, int y_pos, int height, int width){
    Object->x = x_pos;
    Object->y = y_pos;
    Object->h = height;
    Object->w = width;
    return 0;
}

SDL_Texture *loadImage(char *location){
    SDL_Surface* imageSurface = IMG_Load(location);
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
    return imageTexture;
}

int initCharacter(
                char *Name,
                Personagem *Character,
                SDL_Renderer *renderer,
                SDL_Texture *imageTexture,
                SDL_Rect *Character_Dest_Rect,
                SDL_Rect *Character_Img_Rendering_Rect,
                int x,
                int y,
                int height,
                int width,
                int size)
    {
    Character->name = Name;
    Character->CROP_RECT_WIDTH = height;
    Character->CROP_RECT_HEIGHT = width;
    Character->Character_Dest_Rect_Size = size;
    Character->renderer = renderer;
    Character->imageTexture = imageTexture;
    Character->ImageObject = Character_Img_Rendering_Rect;
    Character->Object = Character_Dest_Rect;

    // Calculate the scale factor to fit the cropped image into the Character_Dest_Rect
    double scaleFactor = (double)Character->Character_Dest_Rect_Size / Character->CROP_RECT_WIDTH;

    // Calculate the scaled dimensions of the cropped image
    int scaledWidth = Character->CROP_RECT_WIDTH * scaleFactor;
    int scaledHeight = Character->CROP_RECT_HEIGHT * scaleFactor;

    // square X and Y
    int squareX = (windowWidth - Character->Character_Dest_Rect_Size) / 2;
    int squareY = (windowHeight - Character->Character_Dest_Rect_Size) / 2;

    // Calculate the position of the scaled image within the Character_Dest_Rect
    int imageX = x + (squareX + (Character->Character_Dest_Rect_Size - scaledWidth) / 2);
    int imageY = y + (squareY + (Character->Character_Dest_Rect_Size - scaledHeight) / 2);

    Character->Img_Rendering_XPosition = 0;
    Character->Img_Rendering_YPosition = 0;
    Character->scaledHeight = scaledHeight;
    Character->scaledWidth = scaledWidth;
    Character->IMAGE_COUNT = 3;
    Character->x = imageX;
    Character->y = imageY;
    Character->speed = 5;
    Character->FramesCount = 60;
    Character->FrameLoop = 0;
    // cropRect
    renderObject(
        Character->ImageObject,
        Character->Img_Rendering_XPosition,
        Character->Img_Rendering_YPosition,
        Character->CROP_RECT_WIDTH,
        Character->CROP_RECT_HEIGHT
    );
    // Draw the character Square
    // Dest rect
    renderObject(
            Character->Object,
            Character->x,
            Character->y,
            Character->scaledHeight,
            Character->scaledWidth
    );
    return 0;
}


int characterAnimationRendering(Personagem *Character){
    /* A variável IMAGE_COUNT tem a quantidade total de caracteres que existem na imagem
       assim se tivermos 3 imagens então vamos contar como sendo 6 pois aí conta-mos todos os valores
       da animação em que 3 imagens vão andar para a frente (Character->CROP_RECT_WIDTH) ou para trás (-Character->CROP_RECT_WIDTH)
    */
    if (Character->FrameLoop == Character->FramesCount)
        if(Character->Img_Rendering_XPosition <= Character->CROP_RECT_WIDTH * Character->IMAGE_COUNT*2){
                Character->FrameLoop = 0;
                return (Character->Img_Rendering_XPosition <= Character->CROP_RECT_WIDTH) ? Character->CROP_RECT_WIDTH : -Character->CROP_RECT_WIDTH;
            }
    Character->FrameLoop += 1;
    return 0;
}



int renderCharacter(Personagem *Character){
    // draw the rect of the image character
    renderObject(
        Character->ImageObject,
        Character->Img_Rendering_XPosition,
        Character->Img_Rendering_YPosition,
        Character->CROP_RECT_WIDTH,
        Character->CROP_RECT_HEIGHT
    );
    // Draw the character Square
    renderObject(
            Character->Object,
            Character->x,
            Character->y,
            Character->scaledHeight,
            Character->scaledWidth
    );
    Character->Img_Rendering_XPosition += characterAnimationRendering(Character);
    return 0;
}
