#include <stdio.h>
#include <SDL2/SDL.h>
#include "paddle.h"
#include "ball.h"\

typedef struct {
	SDL_Event event;
	int isRunning;
	int isPaused;

	// Players
	Paddle player1;
	Paddle player2;

	// Ball
	Ball ball;

	// Other
	SDL_Window* window;
	SDL_Renderer* renderer;
	// Add audio back in towards the end.
	//Audio audio;
} Game;



// OLD CODE
//struct Controller {
//	int yDir;
//	SDL_GameController* controller;
//};

//struct Game {
//	int isRunning;
//	SDL_Window* window;
//	SDL_Renderer* renderer;
//	struct Controller controller1;
//	struct Controller controller2;
//};

//struct Box {
//        float x;
//        float y;
//        float width;
//        float height;
//};

/**
 * Constructor of the game class. It initializes every game entity.
 */
void initializeGame();

/**
 * @brief Handle all the events of the game, such as key press.
 */
void handleGameEvents();

/**
 * Update all the game logic, such as a paddle movement request, or
 * move the ball.
 */
void updateGame();

/**
 * Render all the entities of the game.
 */
void renderGame();

/**
* Pause and unpause the game, toggling the m_pause variable.
*/
void pause();

/**
* render_score
*/
void render_score();

/**
* update_game_state
*/
void update_game_state();

/**
* Restart the game state, setting values of ball, paddles position
* and score to default.
*/
void restart_game();

/**
* Reset the game state, i.e. setting the score player values to
* default and hence the position of entities in the game.
*/
void reset_game();

void deinitializeGame();
