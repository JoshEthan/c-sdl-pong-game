/*
 * Core game logic and loop.
 * */

#include <stdlib.h>
#include "game.h"

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

int JOYSTICK_DEAD_ZONE = 8000;
const int SPEED = 150;

int last_frame_time = 0;
struct Box ball;
struct Box paddle1;
struct Box paddle2;

float x = 0.0;
float y = 0.0;
int topPadding = 100;

void gameSetup();
int checkCollision();

void initializeGame(struct Game* game, char* title, int w, int h) {
	game->isRunning = 1;

	x = (float)rand()/(float)(RAND_MAX/1);
	y = (float)rand()/(float)(RAND_MAX/1);

	printf("%f", x);

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
				//printf("Controller 1: %i\n", event.caxis.value);
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
				//printf("Controller 2: %i\n", event.caxis.value);
			}        
                }
        }
}

void gameSetup() {
	// Create an array of rectangles.
	// Then in the render function we need to render the array. Loop through it, etc.
	// Create Score text.
	ball.x = 770;
	ball.y = 200;
	ball.width = 15;
	ball.height = 15;

	paddle1.x = 20;
	paddle1.y = 120;
	paddle1.width = 15;
	paddle1.height = 60;
	
	paddle2.x = 770;
	paddle2.y = 120;
	paddle2.width = 15;
	paddle2.height = 60;
}

void renderGame(struct Game* game) {
        SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	SDL_Rect ball_rect = {
                ball.x,
                ball.y,
                ball.width,
                ball.height
        };
	
	SDL_Rect paddle1_rect = {
                paddle1.x,
                paddle1.y,
                paddle1.width,
                paddle1.height
        };
	
	SDL_Rect paddle2_rect = {
                paddle2.x,
                paddle2.y,
                paddle2.width,
                paddle2.height
        };

	SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);

        SDL_RenderFillRect(game->renderer, &ball_rect);
        SDL_RenderFillRect(game->renderer, &paddle1_rect);
        SDL_RenderFillRect(game->renderer, &paddle2_rect);
        
	SDL_RenderPresent(game->renderer);
}

void updateGame(struct Game* game) {
        int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);

        if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
                SDL_Delay(time_to_wait);
        }

        float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

        last_frame_time = SDL_GetTicks();

	int velocity1 = game->controller1.yDir * SPEED * delta_time;
	int velocity2 = game->controller2.yDir * SPEED * delta_time;

        if(paddle1.y < topPadding && velocity1 > 0) {
        	paddle1.y += game->controller1.yDir * SPEED * delta_time;
	} else if(paddle1.y > 520 && velocity1 < 0) {
		paddle1.y += game->controller1.yDir * SPEED * delta_time;
	} else if(paddle1.y > topPadding && paddle1.y < 520) {
		paddle1.y += game->controller1.yDir * SPEED * delta_time;
	}

        if(paddle2.y < topPadding && velocity2 > 0) {
		paddle2.y += game->controller2.yDir * SPEED * delta_time;
	} else if(paddle2.y > 520 && velocity2 < 0) {
		paddle2.y += game->controller2.yDir * SPEED * delta_time;
	} else if(paddle2.y > topPadding && paddle2.y < 520) {
		paddle2.y += game->controller2.yDir * SPEED * delta_time;
	}

	// Update the Ball
	//ball.x += x * SPEED * delta_time;
        //ball.y += y * SPEED * delta_time;

	if(checkCollision(ball, paddle2)) {
		printf("They are colliding.\n");
	}
}

int checkCollision(struct Box a, struct Box b) {
	//The sides of the rectangles
    	int leftA, leftB;
    	int rightA, rightB;
    	int topA, topB;
    	int bottomA, bottomB;

	//Calculate the sides of rect A
    	leftA = a.x;
    	rightA = a.x + a.width;
    	topA = a.y;
    	bottomA = a.y + a.height;

    	//Calculate the sides of rect B
    	leftB = b.x;
    	rightB = b.x + b.width;
    	topB = b.y;
    	bottomB = b.y + b.height;
     	
	if(bottomA <= topB) {
        	return 0;
    	}

    	if(topA >= bottomB) {
        	return 0;
    	}

    	if(rightA <= leftB) {
        	return 0;
    	}

    	if(leftA >= rightB) {
        	return 0;
    	}

	return 1;
}

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
