#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <stdio.h>

int main()
{
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  
  Uint32 color = 0xFFFFFFFF;  

  SDL_Rect pl1 = (SDL_Rect) {40, 40, 40, 200};
  SDL_FillRect(surface, &pl1, color);
 
  SDL_Rect pl2 = (SDL_Rect) {560, 120, 40, 200};
  SDL_FillRect(surface, &pl2, color);

  SDL_UpdateWindowSurface(window);


  int running = 1;
  SDL_Event event;
  while (running)
  {
    SDL_PollEvent(&event);

    if (event.type == SDL_QUIT)
    {
      running = 0;
    }
    if (event.type == SDL_KEYDOWN)
    {
      printf("key pressed\n");
    }

    SDL_Delay(1);
  }

}
