#include <SDL2/SDL.h>

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



  int running = 1;
  SDL_Event event;
  while (running)
  {
    SDL_PollEvent(&event);
    SDL_UpdateWindowSurface(window);
      
    if (event.type == SDL_QUIT)
    {
      running = 0;
    }

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_UP)
      {
        SDL_FillRect(surface, &pl1, 0x00000000);
        pl1.y -= 10;
        SDL_FillRect(surface, &pl1, color);
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        SDL_FillRect(surface, &pl1, 0x00000000);
        pl1.y += 10;
        SDL_FillRect(surface, &pl1, color);
      }
    }
    
    SDL_Delay(1);
  }

}
