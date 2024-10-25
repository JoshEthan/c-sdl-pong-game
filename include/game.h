#include <stdio.h>
#include <SDL2/SDL.h>

extern int is_game_running;

int initialize_window(void);
int setup();
void update();
void render();
void deinitialize();
