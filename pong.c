#include <SDL2/SDL.h>

#define  MOVEMENT_SPEED 10

void move_rect(SDL_Surface* surface, SDL_Rect * rect, int down)
{
  SDL_FillRect(surface, rect, 0x00000000);
  rect->y += down;
  SDL_FillRect(surface, rect, 0xFFFFFFFF);
}

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
      
    if (event.type == SDL_QUIT)
    {
      running = 0;
    }

    if (event.type == SDL_KEYDOWN)
    {
      if (event.key.keysym.sym == SDLK_UP)
      {
        move_rect(surface, &pl2, -MOVEMENT_SPEED);
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        move_rect(surface, &pl2, MOVEMENT_SPEED);
      }
      
      if (event.key.keysym.sym == SDLK_z)
      {
        move_rect(surface, &pl1, -MOVEMENT_SPEED);
      }
      if (event.key.keysym.sym == SDLK_s)
      {
        move_rect(surface, &pl1, MOVEMENT_SPEED);
      }
    }
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(1);
  }
}
