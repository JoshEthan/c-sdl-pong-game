#include <SDL2/SDL.h>

typedef struct{
	SDL_Rect rect;
//	PlayerScore score;
	int controls[2];
	int width;
	int height;
} Paddle;
