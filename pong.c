#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>

int main()
{
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  
  SDL_Rect rect = (SDL_Rect) {0, 40, 40, 40};
  Uint32 color = 0xFFFFFFFF;
  SDL_FillRect(surface, &rect, color);
  SDL_UpdateWindowSurface(window);

  SDL_Delay(5000);

}
