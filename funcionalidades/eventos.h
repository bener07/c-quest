
const int squareSize = 32;


int QUIT = 0;
int characterX = (windowWidth / 2 - squareSize /2);
int characterY = (windowHeight / 2 - squareSize /2);
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
                    // character movement in the box
                    case SDLK_UP:
                    // in case the caracter is hitting the 0 position or lower, it gets near its
                        characterY -= (characterY <= 2 ) ? 0 : SPEED;
                        break;
                    case SDLK_DOWN:
                        characterY += (characterY+squareSize >= windowHeight) ? windowHeight - (characterY+squareSize) : SPEED;
                        break;
                    case SDLK_LEFT:
                        characterX -= (characterX <= 2) ? (characterX) : SPEED;
                        break;
                    case SDLK_RIGHT:
                        characterX += (characterX+squareSize >= windowWidth) ? windowWidth - (characterX+squareSize) : SPEED;
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
