/*
 * Copyright 2024 Joshua Rolph
 *
 * The entry point of the application.
 * 
 * */

#include "game.h"

int main(int argc, char *argv[]) {
	Game game = {0};

	initializeGame(&game);

//	while(game.isRunning) {
//		handleGameEvents(&game);
//		updateGame(&game);
//		renderGame(&game);
//	}

	deinitializeGame(&game);

	return 0;
}
