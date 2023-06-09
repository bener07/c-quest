typedef struct {
    SDL_Renderer *renderer;
    SDL_Texture *imageTexture;
    SDL_Rect *Object;
    SDL_Rect *ImageObject;
    SDL_Rect position;
    int Img_Rendering_XPosition;
    int Img_Rendering_YPosition;
    int scaledHeight;
    int scaledWidth;
    int IMAGE_COUNT;
    int Character_Dest_Rect_Size;
    int FramesCount;
    int FrameLoop;
    char *name;
    int speed;
    int life;
    int gameOver;
    int mapCount;
} Personagem;


typedef struct{
    SDL_Texture *imageTexture;
    SDL_Rect *Object;
    SDL_Rect *ImageObject;
    SDL_Rect position;
    SDL_PixelFormat *format;
    char *objectName;
    int Img_Rendering_XPosition;
    int Img_Rendering_YPosition;
    int IMAGE_COUNT;
    int FramesCount;
    int FrameLoop;
    int imageOriginalWidth;
    int imageOriginalHeight;
    int Dest_Rect_Size;
    int scaledHeight;
    int scaledWidth;
    int exists;
} Objeto;

typedef struct{
    SDL_Texture *panelTexture;
    SDL_Rect *textRect;
    SDL_Rect *panelRect;
    TTF_Font *font;
    char *text;
    char *titulo;
    int textX;
    int textY;
    int textHeight;
    int textWidth;
    int x;
    int y;
    int h;
    int w;
} Painel;

typedef enum {
    TILE_FLOOR,
    TILE_WALL
} TileType;

typedef struct {
    TileType** tiles;
    int width;
    int height;
} TileMap;

typedef struct {
    TileMap *map;
    SDL_Texture *imageTexture;
    SDL_Rect *Object;
    SDL_Rect position;
    char *objectName;
} Mapa;