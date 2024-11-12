#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
    // TTF_Font* font;
} Multimedia;

/**
 * Constructor of the multimedia struct. It initializes the multimedia entity.
 */
int initializeMultimedia();

void deinitializeMultimedia();
