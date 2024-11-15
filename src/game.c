/*
 * Core game logic and loop.
 * */

#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "game.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

int JOYSTICK_DEAD_ZONE = 8000;
const int SPEED = 150;

void initializeGame(Game* game) {
	// Initialize SDL
	if(initializeMultimedia(&game->sdl)) {
		// Game State
		game->isPaused = 1;
		game->isRunning = 0;
	} else {
		game->isRunning = 1;
	}

	// Player 1
	game->player1.paddle = (SDL_Rect){ 0, 120 / 2, 16, 64};

	// Player 2
	game->player2.paddle = (SDL_Rect){ 600, 120/2, 16, 64};

	// Ball
}

void handleGameEvents(Game* game) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch(event.type) {
		case SDL_QUIT:
			game->isRunning = 0;
			break;
                case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_ESCAPE) {
                                game->isRunning = 0;
                        }
                        break;
	}


  	while(SDL_PollEvent(&event)) {
    		switch(event.type){
      			case SDL_KEYDOWN:
        			printf("Key press detected\n");
				switch( event.key.keysym.sym ){
					case SDLK_UP:
						printf("Up key press!\n");
						break;
					case SDLK_DOWN:
						printf("Down key press!\n");
						break;

				}
			case SDL_KEYUP:
				printf("Key up now.\n");
				break;
			default:
				break;
		}
	}

}


void renderGame(Game* game) {
        SDL_SetRenderDrawColor(game->sdl.renderer, 36, 40, 59, 255);
	SDL_RenderClear(game->sdl.renderer);

	SDL_SetRenderDrawColor(game->sdl.renderer, 192, 202, 245, 255);
        SDL_RenderFillRect(game->sdl.renderer, &game->player1.paddle);

	SDL_SetRenderDrawColor(game->sdl.renderer, 247, 118, 142, 255);
        SDL_RenderFillRect(game->sdl.renderer, &game->player2.paddle);

	SDL_RenderPresent(game->sdl.renderer);
}

void updateGame(Game* game) {

}

void deinitializeGame(Game* game) {
	deinitializeMultimedia(&game->sdl);
}
