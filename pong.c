#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

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

  SDL_Delay(5000);

}
