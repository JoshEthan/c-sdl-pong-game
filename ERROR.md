src/multimedia.c:15:33: warning: ‘struct Multimedia’ declared inside parameter list will not be visible outside of this definition or declaration
   15 | int initializeMultimedia(struct Multimedia* multimedia) {
      |                                 ^~~~~~~~~~
src/multimedia.c: In function ‘initializeMultimedia’:
src/multimedia.c:20:9: error: expected ‘;’ before ‘}’ token
   20 |         }
      |         ^
src/multimedia.c:23:19: error: invalid use of undefined type ‘struct Multimedia’
   23 |         multimedia->window = SDL_CreateWindow(
      |                   ^~
src/multimedia.c:32:23: error: invalid use of undefined type ‘struct Multimedia’
   32 |         if(!multimedia->window) {
      |                       ^~
src/multimedia.c:36:9: error: expected ‘;’ before ‘}’ token
   36 |         }
      |         ^
src/multimedia.c:39:19: error: invalid use of undefined type ‘struct Multimedia’
   39 |         multimedia->renderer = SDL_CreateRenderer(multimedia->window, -1, 0);
      |                   ^~
src/multimedia.c:39:61: error: invalid use of undefined type ‘struct Multimedia’
   39 |         multimedia->renderer = SDL_CreateRenderer(multimedia->window, -1, 0);
      |                                                             ^~
src/multimedia.c:41:23: error: invalid use of undefined type ‘struct Multimedia’
   41 |         if(!multimedia->renderer) {
      |                       ^~
src/multimedia.c:43:45: error: invalid use of undefined type ‘struct Multimedia’
   43 |                 SDL_DestroyWindow(multimedia->window);
      |                                             ^~
src/multimedia.c:46:9: error: expected ‘;’ before ‘}’ token
   46 |         }
      |         ^
src/multimedia.c: At top level:
src/multimedia.c:66:36: warning: ‘struct Multimedia’ declared inside parameter list will not be visible outside of this definition or declaration
   66 | void deinitializeMultimedia(struct Multimedia* multimedia) {
      |                                    ^~~~~~~~~~
src/multimedia.c: In function ‘deinitializeMultimedia’:
src/multimedia.c:67:39: error: invalid use of undefined type ‘struct Multimedia’
   67 |         SDL_DestroyRenderer(multimedia->renderer);
      |                                       ^~
src/multimedia.c:68:37: error: invalid use of undefined type ‘struct Multimedia’
   68 |         SDL_DestroyWindow(multimedia->window);
      |                                     ^~
make: *** [Makefile:16: build/multimedia.o] Error 1

