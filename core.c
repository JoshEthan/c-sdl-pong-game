#include "core.h"

int is_game_running = 0;

// Window setup
SDL_Window* window = NULL;
char window_title[] = "Pong";
int window_w = 800;
int window_h = 600;

// Render Setup
SDL_Renderer* renderer = NULL;

int initialize_window(void) {
	if(SDL_Init(SDL_INIT_TIMER) != 0) {
		fprintf(stderr, "Error initializing SDL.\n");
		return 0;
	}

	window = SDL_CreateWindow(
		window_title,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		window_w,
		window_h,
		0
	);

	if(!window) {
		fprintf(stderr, "Error creating window!\n");
		return 0;
	}

	return 1;
}

int SDL_setup() {
	renderer = SDL_CreateRenderer(window, -1, 0);

	if(!renderer) {
		fprintf(stderr, "Error creating renderer!\n");
		return 0;
	}

	return 1;
}

int game_setup() {
	// Create an array of rectangles.
	// Then in the render function we need to render the array. Loop through it, etc.
	// Create Score text.
	// Create Paddles.
	// Setup Ball.
}

int setup() {
	if(!SDL_setup()) {
		printf("SDL_Setup failed.");
		return 0;
	}

	return 1;
}

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

}

void render() {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void update() {}

void deinitialize() {
	SDL_DestroyRenderer(renderer);

        //Close game controller
        //SDL_GameControllerClose( gGameController );
        //gGameController = NULL;

        SDL_DestroyWindow(window);
        SDL_Quit();
}
