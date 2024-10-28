/*
 * The entry point of the application.
 * */

#include "game.h"

int main(int argc, char *argv[]) {
	struct Game game = {0};
	printf("Initializing game...\n");
	initializeGame(&game, "Pong", 800, 600);

	while(game.isRunning) {
		handleGameEvents(&game);
		updateGame(&game);
		renderGame(&game);
	}

	printf("De-initializing game...\n");
	deinitializeGame(&game);

	return 0;
}
