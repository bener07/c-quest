int QUIT = 0;
int FRAME_DELAY = 300;

void characterMovement(Personagem *Character, Objeto *Room, SDL_Event event) {
    switch (event.key.keysym.sym) {
        // character movement in the box
        case SDLK_w:
        case SDLK_UP:
            Character->Img_Rendering_YPosition = Character->position.h*5;
            Character->position.y -= (Character->position.y <= 2) ? 0 : Character->speed;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            Character->Img_Rendering_YPosition = Character->position.h*3;
            Character->position.y += (Character->position.y+Character->Character_Dest_Rect_Size >= windowHeight) ? windowHeight - (Character->position.y+Character->Character_Dest_Rect_Size) : Character->speed;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            Character->Img_Rendering_YPosition = Character->position.h*6;
            Character->position.x -= (Character->position.x <= 2) ? (Character->position.x) : Character->speed;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            Character->Img_Rendering_YPosition = Character->position.h*4;
            Character->position.x += (Character->position.x+Character->Character_Dest_Rect_Size >= windowWidth) ? windowWidth - (Character->position.x+Character->Character_Dest_Rect_Size) : Character->speed;
            break;
        default:
            break;
    }
}

void ImagePositionZero(Personagem *Character){
    Character->Img_Rendering_YPosition = 0;
    Character->Img_Rendering_XPosition = 0;
}