int QUIT = 0;
int FRAME_DELAY = 300;

void handleEvents(Personagem *Character) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                QUIT = !QUIT;
                break;
            case SDL_KEYDOWN:
                // Handle key press events
                switch (event.key.keysym.sym) {
                    // character movement in the box
                    case SDLK_UP:
                    // in case the caracter is hitting the 0 position or lower, it gets near its
                        Character->Img_Rendering_YPosition = 32;
                        Character->y -= (Character->y <= 2 ) ? 0 : Character->speed;
                        break;
                    case SDLK_DOWN:
                        Character->Img_Rendering_YPosition = 48;
                        Character->y += (Character->y+Character->Character_Dest_Rect_Size >= windowHeight) ? windowHeight - (Character->y+Character->Character_Dest_Rect_Size) : Character->speed;
                        break;
                    case SDLK_LEFT:
                        Character->Img_Rendering_YPosition = 16;
                        // Character_Rendering_YPosition = (Character_Rendering_YPosition == CROP_RECT_HEIGHT) ? Character_Rendering_YPosition : CROP_RECT_HEIGHT;
                        Character->x -= (Character->x <= 2) ? (Character->x) : Character->speed;
                        break;
                    case SDLK_RIGHT:
                        Character->Img_Rendering_YPosition = 16;
                        printf("To right\n");
                        Character->x += (Character->x+Character->Character_Dest_Rect_Size >= windowWidth) ? windowWidth - (Character->x+Character->Character_Dest_Rect_Size) : Character->speed;
                        break;
                    default:
                        break;
                }
                break;
            default:
                Character->Img_Rendering_YPosition = 0;
                Character->Img_Rendering_XPosition = 0;
                break;
        }
    }
}
