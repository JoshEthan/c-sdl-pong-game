#include <SDL2/SDL.h>

//Analog joystick dead zone
const int GAMECONTROLLER_DEAD_ZONE = 8000;
const int SPEED = 150;

SDL_GameController* gGameController = NULL;

struct controller {
	float yDir;
	SDL_GameController* gGameController;
} controller_1, controller_2;

void process_input() {
	SDL_Event event;
	SDL_PollEvent(&event);
        
	switch(event.type) {
                case SDL_QUIT:
                        is_game_running = 0;
                        break;
                case SDL_KEYDOWN:
                        if(event.key.keysym.sym == SDLK_ESCAPE) {
                                is_game_running = 0;
                        }
                        break;
        }

	// Poll
        while (SDL_PollEvent(&event)) {
                if(event.type == SDL_CONTROLLERAXISMOTION) {
			//Motion on controller 0
                        if( event.caxis.which == 0 ) {
                        	if(event.caxis.axis == 1) {
                                	if(event.caxis.value > GAMECONTROLLER_DEAD_ZONE) {
                                		controller_1.yDir = 1;
                                	} else if(event.caxis.value < -GAMECONTROLLER_DEAD_ZONE) {
                                        	controller_1.yDir = -1;
                                	} else {
                                		controller_1.yDir = 0;
                                	}
                        	}
				printf("Controller 1: %i\n", event.caxis.value);
                	} else if(event.caxis.which == 1) {
				if(event.caxis.axis == 1) {
                                	if(event.caxis.value > GAMECONTROLLER_DEAD_ZONE) {
                                		controller_2.yDir = 1;
                                	} else if(event.caxis.value < -GAMECONTROLLER_DEAD_ZONE) {
                                        	controller_2.yDir = -1;
                                	} else {
                                		controller_2.yDir = 0;
                                	}
                        	}
				printf("Controller 2: %i\n", event.caxis.value);

			}
        	}
	}
}
