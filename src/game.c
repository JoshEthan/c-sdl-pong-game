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

int last_frame_time = 0;

float x = 0.0;
float y = 0.0;
int topPadding = 100;

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
	game->player2.paddle = (SDL_Rect){ 0, 120 / 2, 16, 64};

	// Ball
}

void handleGameEvents(Game* game) {
}


void renderGame(Game* game) {
}

void updateGame(Game* game) {

}

void deinitializeGame(Game* game) {
	deinitializeMultimedia(&game->sdl);
}
