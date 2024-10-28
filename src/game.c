/*
 * Core game logic and loop.
 * */

#include <stdlib.h>
#include "game.h"

int JOYSTICK_DEAD_ZONE = 8000;

struct Box ball;

void gameSetup();

void initializeGame(struct Game* game, char* title, int w, int h) {
	game->isRunning = 1;

	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Error initializing SDL.\n");
		game->isRunning = 0;
	}

	game->window = SDL_CreateWindow(
		title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w,
		h,
		0
	);

	if(!game->window) {
		fprintf(stderr, "Error creating window!\n");
		game->isRunning = 0;
	}
	
	game->renderer = SDL_CreateRenderer(game->window, -1, 0);

	if(!game->renderer) {
		fprintf(stderr, "Error creating renderer!\n");
		game->isRunning = 0;
	}

	//Check for game controllers
        switch(SDL_NumJoysticks()) {
		case 0:
 			printf("Warning: No controllers connected!\n");
			break;
		case 1:
			printf("Warning: Only one controller connected!\n");
			break;
		case 2:
			//Load game controllers
			game->controller1.controller = SDL_GameControllerOpen(0);
			game->controller2.controller = SDL_GameControllerOpen(1);
			break;
	}

	gameSetup();
}

void handleGameEvents(struct Game* game) {
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
	
	// Poll
        while (SDL_PollEvent(&event)) {
                if(event.type == SDL_CONTROLLERAXISMOTION) {
			if(event.caxis.which == 0) {
                        	if(event.caxis.axis == 1) {
                                	if(event.caxis.value > JOYSTICK_DEAD_ZONE) {
                                        	game->controller1.yDir = 1;
                                	} else if(event.caxis.value < -JOYSTICK_DEAD_ZONE) {
                                        	game->controller1.yDir = -1;
                                	} else {
                                        	game->controller1.yDir = 0;
                                	}
                        	}
				printf("Controller 1: %i\n", event.caxis.value);
			} else if(event.caxis.which == 1) {
                        	if(event.caxis.axis == 1) {
                                	if(event.caxis.value > JOYSTICK_DEAD_ZONE) {
                                        	game->controller2.yDir = 1;
                                	} else if(event.caxis.value < -JOYSTICK_DEAD_ZONE) {
                                        	game->controller2.yDir = -1;
                                	} else {
                                        	game->controller2.yDir = 0;
                                	}
                        	}
				printf("Controller 2: %i\n", event.caxis.value);
			}        
                }
        }
}

void gameSetup() {
	// Create an array of rectangles.
	// Then in the render function we need to render the array. Loop through it, etc.
	// Create Score text.
	// Create Paddles.
	// Setup Ball.
	ball.x = 20;
	ball.y = 20;
	ball.width = 15;
	ball.height = 150;
}

//int setup() {
//	if(!SDL_setup()) {
//		printf("SDL_Setup failed.");
//		return 0;
//	}
//
//	return 1;
//}

void renderGame(struct Game* game) {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);
	SDL_RenderPresent(game->renderer);

	SDL_Rect ball_rect = {
                ball.x,
                ball.y,
                ball.width,
                ball.height
        };

	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(game->renderer, &ball_rect);

        SDL_RenderPresent(game->renderer);
}

void updateGame(struct Game* game) {}

void deinitializeGame(struct Game* game) {
	SDL_DestroyRenderer(game->renderer);

	//Check for game controllers
        switch(SDL_NumJoysticks()) {
		case 0:
 			printf("Warning: No controllers to diconnect!\n");
			break;
		case 1:
			printf("Warning: Only one controller to disconnect!\n");
			break;
		case 2:
			//Close game controllers
			SDL_GameControllerClose(game->controller1.controller);
			game->controller1.controller = NULL;
			SDL_GameControllerClose(game->controller2.controller);
			game->controller2.controller = NULL;
			break;
	}
       
	SDL_DestroyWindow(game->window);
        SDL_Quit();
}
