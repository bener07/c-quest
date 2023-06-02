int QUIT = 0;
int FRAME_DELAY = 300;

void handleEvents(Personagem *Character, SDL_Event event) {
    switch (event.key.keysym.sym) {
        // character movement in the box
        case SDLK_w:
        case SDLK_UP:
            Character->Img_Rendering_YPosition = Character->CROP_RECT_HEIGHT*5;
            Character->y -= (Character->y <= 2 ) ? 0 : Character->speed;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            Character->Img_Rendering_YPosition = Character->CROP_RECT_HEIGHT*3;
            Character->y += (Character->y+Character->Character_Dest_Rect_Size >= windowHeight) ? windowHeight - (Character->y+Character->Character_Dest_Rect_Size) : Character->speed;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            Character->Img_Rendering_YPosition = Character->CROP_RECT_HEIGHT*6;
            Character->x -= (Character->x <= 2) ? (Character->x) : Character->speed;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            Character->Img_Rendering_YPosition = Character->CROP_RECT_HEIGHT*4;
            Character->x += (Character->x+Character->Character_Dest_Rect_Size >= windowWidth) ? windowWidth - (Character->x+Character->Character_Dest_Rect_Size) : Character->speed;
            break;
        default:
            break;
    }
}

void ImagePositionZero(Personagem *Character){
    Character->Img_Rendering_YPosition = 0;
    Character->Img_Rendering_XPosition = 0;
}