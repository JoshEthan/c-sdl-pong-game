/*
 * The entry point of the application.
 * */

#include <stdio.h>
#include <SDL2/SDL.h>
#include "game.h"

int main() {
	printf("Hello World!\n");
	is_game_running = initialize_window();

	setup();

	while(is_game_running) {
		process_input();
//		update();
		render();
	}

	deinitialize();

	return 0;
}
