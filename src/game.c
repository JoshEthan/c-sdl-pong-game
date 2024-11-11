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
struct Box ball;
struct Box paddle1;
struct Box paddle2;

float x = 0.0;
float y = 0.0;
int topPadding = 100;

void gameSetup();
int checkCollision();

void initializeGame(struct Game* game) {
	// Initialize SDL
	if(initializeMultimedia(&game->sdl)) {
		// Game State
		game->isPaused = 1;
		game->isRunning = 0;
	} else {
		game->isRunning = 1;
	}

	// Player 1
	player1->paddle = { 0, 120 / 2, 16, 64};

	// Player 2
	player2->paddle = { 0, 120 / 2, 16, 64};

	// Ball
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
     
	// These return false. Meaning there is no collision if hey are true.
	// Such as, if A-botom is less-than OR higher THAN B-top.
	// These normally return FALSE
	if(bottomA <= topB) {
        	return 0;
    	} else {
		printf("Is colliding! in the Check function!\n");
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
	deinitializeMultimedia(&game->sdl);

	//Check for game controllers
    //     switch(SDL_NumJoysticks()) {
	// 	case 0:
 	// 		printf("Warning: No controllers to diconnect!\n");
	// 		break;
	// 	case 1:
	// 		printf("Warning: Only one controller to disconnect!\n");
	// 		break;
	// 	case 2:
	// 		//Close game controllers
	// 		SDL_GameControllerClose(game->controller1.controller);
	// 		game->controller1.controller = NULL;
	// 		SDL_GameControllerClose(game->controller2.controller);
	// 		game->controller2.controller = NULL;
	// 		break;
	// }
}
