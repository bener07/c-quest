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

SDL_Texture *loadImage(char *location, Objeto* objeto){
    SDL_Surface* imageSurface = IMG_Load(location);
    objeto->position.w = imageSurface->w;
    objeto->position.h = imageSurface->h;
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
                char *imageLocation,
                Personagem *Character,
                SDL_Renderer *renderer,
                int x,
                int y,
                int height,
                int width,
                int size,
                int speed)
    {
    Character->name = Name;
    Character->position.w = width;
    Character->position.h = height;
    Character->Character_Dest_Rect_Size = size;
    Character->renderer = renderer;
    Character->imageTexture = loadImage(imageLocation, Character);
    SDL_Rect *Character_Img_Rendering_Rect = malloc(sizeof(SDL_Rect));
    Character->ImageObject = Character_Img_Rendering_Rect;
    SDL_Rect *Character_Dest_Rect = malloc(sizeof(SDL_Rect));
    Character->Object = Character_Dest_Rect;

    // Calculate the scale factor to fit the cropped image into the Character_Dest_Rect
    double scaleFactor = (double)Character->Character_Dest_Rect_Size / Character->position.w;

    // Calculate the scaled dimensions of the cropped image
    int scaledWidth = Character->position.w * scaleFactor;
    int scaledHeight = Character->position.h * scaleFactor;

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
    Character->position.x = imageX;
    Character->position.y = imageY;
    Character->speed = speed;
    Character->FramesCount = speed*30;
    Character->FrameLoop = 0;
    // cropRect
    renderObject(
        Character->ImageObject,
        Character->Img_Rendering_XPosition,
        Character->Img_Rendering_YPosition,
        Character->position.h,
        Character->position.w
    );
    // Draw the character Square
    // Dest rect
    renderObject(
            Character->Object,
            Character->position.x,
            Character->position.y,
            Character->scaledHeight,
            Character->scaledWidth
    );
    SDL_RenderCopy(renderer, Character->imageTexture, Character->ImageObject, NULL);
    return 0;
}


int characterAnimationRendering(Personagem *Character){
    /* A variável IMAGE_COUNT tem a quantidade total de caracteres que existem na imagem
       assim se tivermos 3 imagens então vamos contar como sendo 6 pois aí conta-mos todos os valores
       da animação em que 3 imagens vão andar para a frente (Character->position.w) ou para trás (-Character->position.w)
    */
    if (Character->FrameLoop == Character->FramesCount)
        if(Character->Img_Rendering_XPosition <= Character->position.w * Character->IMAGE_COUNT*2){
                Character->FrameLoop = 0;
                return (Character->Img_Rendering_XPosition <= Character->position.w) ? Character->position.w : -Character->position.w;
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
        Character->position.w,
        Character->position.h
    );
    // Draw the character Square
    renderObject(
            Character->Object,
            Character->position.x,
            Character->position.y,
            Character->scaledHeight,
            Character->scaledWidth
    );
    SDL_RenderCopyEx(renderer, Character->imageTexture, Character->ImageObject, Character->Object, 0, NULL, SDL_FLIP_NONE);
    Character->Img_Rendering_XPosition += characterAnimationRendering(Character);
    return 0;
}


int renderGameObject(Objeto *objeto){
    // Draw the character Square
    renderObject(
        objeto->Object,
        objeto->position.x,
        objeto->position.y,
        objeto->position.h,
        objeto->position.w
    );
    SDL_RenderCopy(renderer, objeto->imageTexture, NULL, &objeto->position);
    return 0;
}


TTF_Font *loadFont(char *location, char size){
    TTF_Font* font = TTF_OpenFont(location, size);
    if (font == NULL) {
        printf("Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return font;
    }
    return font;
}

int initObject(
                Objeto *objeto,
                char *Name,
                int x,
                int y,
                char *imageLocation){
    objeto->format = SDL_AllocFormat(SDL_GetWindowPixelFormat(window));
    if (objeto->format == NULL) {
        printf("Failed to allocate pixel format: %s\n", SDL_GetError());
        SDL_DestroyTexture(objeto->imageTexture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
    }
    objeto->objectName = Name;
    objeto->imageTexture = loadImage(imageLocation, objeto);
    printf("Width: %d\nHeight: %d\n", objeto->position.w, objeto->position.h);

    SDL_Rect *Dest_Rect = malloc(sizeof(SDL_Rect));
    objeto->Object = Dest_Rect;


    // Calculate the position of the scaled image within the Character_Dest_Rect
    objeto->position.x = x + (windowWidth - objeto->position.w) / 2;
    objeto->position.y = y + (windowHeight - objeto->position.h) / 2;

    // Draw the character Square
    // Dest rect
    renderObject(
            objeto->Object,
            objeto->position.x,
            objeto->position.y,
            objeto->position.h,
            objeto->position.w
    );
    SDL_RenderCopy(renderer, objeto->imageTexture, NULL, &objeto->position);
    return 0;
}

int createPanel(Painel *panel,
                char *font_location,
                int font_size,
                char *textContent,
                char *panelTitle,
                int panelXLocation,
                int panelYLocation,
                int panelWidth,
                int panelHeight,
                int textX,
                int textY,
                int textWidth,
                int textHeight,
                SDL_Color textColor
                ){
    TTF_Font *font = loadFont(font_location, font_size);
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textContent, textColor);
    if (textSurface == NULL) {
        printf("Failed to create text surface: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }
    SDL_FreeSurface(textSurface);
    SDL_Rect *panelRect = malloc(sizeof(SDL_Rect));
    panelRect->x = panelXLocation;
    panelRect->y = panelYLocation;
    panelRect->h = panelHeight;
    panelRect->w = panelWidth;


    SDL_RenderFillRect(renderer, panelRect);

    SDL_Rect *textRect = malloc(sizeof(SDL_Rect));
    textRect->x = textX;
    textRect->y = textY;
    textRect->h = textHeight;
    textRect->w = textWidth;

    panel->panelTexture = textTexture;
    panel->panelRect = panelRect;
    panel->textRect = textRect;
    panel->titulo = panelTitle;
    panel->text = textContent;
    panel->font = font;
    panel->textHeight = textHeight;
    panel->textWidth = textWidth;
    panel->textX = textX;
    panel->textY = textY;
    panel->x = panelXLocation;
    panel->y = panelYLocation;
    panel->w = panelHeight;
    panel->h = panelWidth;
    return 0;
}

int renderPanel(Painel *panel){
    SDL_QueryTexture(panel->panelTexture, NULL, NULL, &panel->textRect->w, &panel->textRect->h);
    SDL_RenderCopy(renderer, panel->panelTexture, NULL, panel->textRect);
    return 0;
}

int DestroyPanel(Painel *panel){
    SDL_DestroyTexture(panel->panelTexture);
    TTF_CloseFont(panel->font);
    return 0;
}


TileMap* loadTileMap(const char* filename) {
    SDL_Surface* imageSurface = IMG_Load(filename);
    if (!imageSurface) {
        printf("Failed to load image: %s\n", IMG_GetError());
        return NULL;
    }

    TileMap* tileMap = (TileMap*)malloc(sizeof(TileMap));
    if (!tileMap) {
        printf("Failed to allocate memory for tile map\n");
        SDL_FreeSurface(imageSurface);
        return NULL;
    }

    tileMap->width = imageSurface->w / windowWidth;
    tileMap->height = imageSurface->h / windowHeight;

    tileMap->tiles = (TileType**)malloc(tileMap->height * sizeof(TileType*));
    if (!tileMap->tiles) {
        printf("Failed to allocate memory for tiles\n");
        free(tileMap);
        SDL_FreeSurface(imageSurface);
        return NULL;
    }

    Uint32* pixels = (Uint32*)imageSurface->pixels;

    for (int y = 0; y < tileMap->height; y++) {
        tileMap->tiles[y] = (TileType*)malloc(tileMap->width * sizeof(TileType));
        if (!tileMap->tiles[y]) {
            printf("Failed to allocate memory for tiles\n");
            for (int i = 0; i < y; i++) {
                free(tileMap->tiles[i]);
            }
            free(tileMap->tiles);
            free(tileMap);
            SDL_FreeSurface(imageSurface);
            return NULL;
        }

        for (int x = 0; x < tileMap->width; x++) {
            Uint8 r, g, b, a;
            SDL_GetRGBA(pixels[(y * TILE_SIZE) * imageSurface->w + (x * TILE_SIZE)], imageSurface->format, &r, &g, &b, &a);
            if (r == 255 && g == 255 && b == 255 && a == 255) {
                tileMap->tiles[y][x] = TILE_WALL;
            } else {
                tileMap->tiles[y][x] = TILE_FLOOR;
            }
        }
    }

    SDL_FreeSurface(imageSurface);

    return tileMap;
}
