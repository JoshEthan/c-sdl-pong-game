/*
 * Multimedia library wrapper.
 * */

// #include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "multimedia.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define SUCCESS 0
#define ERROR -1

int initializeMultimedia(struct Multimedia* multimedia) {
	// SDL INITIALIZATION
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "Error initializing SDL: %s\n", SDL_GetError());
		return ERROR
	}

	// WINDOW CREATION
	multimedia->window = SDL_CreateWindow(
		"Pong",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		0
	);

	if(!multimedia->window) {
		fprintf(stderr, "Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return ERROR
	}
	
	// RENDER CREATION
	multimedia->renderer = SDL_CreateRenderer(multimedia->window, -1, 0);

	if(!multimedia->renderer) {
		fprintf(stderr, "Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(multimedia->window);
        SDL_Quit();
		return ERROR
	}

	// GAME CONTROLLERS
    // switch(SDL_NumJoysticks()) {
	// 	case 0:
 	// 		printf("Warning: No controllers connected!\n");
	// 		break;
	// 	case 1:
	// 		printf("Warning: Only one controller connected!\n");
	// 		break;
	// 	case 2:
	// 		//Load game controllers
	// 		multimedia->controller1.controller = SDL_GameControllerOpen(0);
	// 		multimedia->controller2.controller = SDL_GameControllerOpen(1);
	// 		break;
	// }

	return SUCCESS;
}

void deinitializeMultimedia(struct Multimedia* multimedia) {
	SDL_DestroyRenderer(multimedia->renderer);
	SDL_DestroyWindow(multimedia->window);
    SDL_Quit();
}