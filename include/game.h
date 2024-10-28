#include <stdio.h>
#include <SDL2/SDL.h>

struct Controller {
	int yDir;
	SDL_GameController* controller;
};

struct Game {
	int isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	struct Controller controller1;
	struct Controller controller2;
};

struct Box {
        float x;
        float y;
        float width;
        float height;
};

struct Game createGame();
void initializeGame();
void handleGameEvents();
void updateGame();
void renderGame();
void deinitializeGame();
