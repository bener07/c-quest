#include <SDL2/SDL.h>
#include <stdlib.h>

// Creates a Panel and returns an Object as a renderer
// it's only to make it easier
int createPanel(SDL_Rect* Object, int x_pos, int y_pos, int height, int width){
    Object->x = x_pos;
    Object->y = y_pos;
    Object->h = height;
    Object->w = width;
    return 0;
}