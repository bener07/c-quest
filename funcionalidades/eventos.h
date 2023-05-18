const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SQUARE_SIZE = 50;


int QUIT = 0;
int characterX = (SCREEN_WIDTH / 2 - SQUARE_SIZE /2);
int characterY = (SCREEN_HEIGHT / 2 - SQUARE_SIZE /2);
int SPEED = 10;

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                QUIT = !QUIT;
                break;
            case SDL_KEYDOWN:
                // Handle key press events
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        characterY -= (characterY <= 0 ) ? 0 : SPEED;
                        break;
                    case SDLK_DOWN:
                        characterY += (characterY+SQUARE_SIZE >= SCREEN_HEIGHT) ? SCREEN_HEIGHT - (characterY+SQUARE_SIZE) : SPEED;
                        break;
                    case SDLK_LEFT:
                        characterX -= SPEED;
                        break;
                    case SDLK_RIGHT:
                        characterX += SPEED;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}
