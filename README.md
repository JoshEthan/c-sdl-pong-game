Pong game recreated using C and SDL.

We are working on re-writing a lot of the code base.

TODO:

- We ran into a lot of errors. So I just cleared out the game file. Figured it is all saved in Git. We need to work through errors in ERROR.md
- We need to work on the while loop next.
- Then we can add controller and input support.
- Then we can add updating the screne and paddles.
- Text
- NETWORKING!

- Redo the init game function. I am deciding if I want to have my own window and render files, OR if I want to just have a SDL file that handles its own setup.
  So we can either do windowInit and RendererInit OR SDLInit(). Seems redundant to have SDLInit if I already have SDLInit... but I kinda think it makes sense to have a function or something that will handle all of the SDL initialization that isn't in the game init.
  struct SDL {} sdl;
  sdlInit();

I can handle all of the font and networking init stuff in the sdl init files. It kinda makes sense since it is its own setup. It just seems redunant to make my own sdl->window when there is already a SDL_Window. You know?
Why makes a struct of a class?

# Resources

In case we somehow lose the web pages:
C++ example - Good file org
https://github.com/rafaelcn/pong-game/blob/master/src/window.hpp

C example
https://github.com/leviaviv28/SDL2-C-Pong/blob/master/Paddle.h
