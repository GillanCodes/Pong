#include <SDL2/SDL.h>

#define MOVEMENT_SPEED 10
#define WHITE_COLOR 0xFFFFFFFF

typedef struct Speed {
  int x;
  int y;
} Speed;

void move_rect(SDL_Surface* surface, SDL_Rect * rect, Speed *speed)
{
  SDL_FillRect(surface, rect, 0x00000000);
  rect->x += speed->x;
  rect->y += speed->y;
  SDL_FillRect(surface, rect, WHITE_COLOR);
}

int main()
{
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  
  SDL_Rect pl1 = (SDL_Rect) {40, 40, 40, 200};
  SDL_FillRect(surface, &pl1, WHITE_COLOR);

  SDL_Rect pl2 = (SDL_Rect) {560, 120, 40, 200};
  SDL_FillRect(surface, &pl2, WHITE_COLOR);

  SDL_Rect ball = (SDL_Rect) {320, 240, 10,10};
  SDL_FillRect(surface, &ball, WHITE_COLOR);

  SDL_Rect border = (SDL_Rect) {320, 0, 1, 480};
  SDL_FillRect(surface, &border, WHITE_COLOR);

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
        Speed speed = (Speed) {0, -MOVEMENT_SPEED};
        move_rect(surface, &pl2, &speed);
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        Speed speed = (Speed) {0, +MOVEMENT_SPEED};
        move_rect(surface, &pl2, &speed);
      }
      
      if (event.key.keysym.sym == SDLK_z)
      {
        Speed speed = (Speed) {0, -MOVEMENT_SPEED};
        move_rect(surface, &pl1, &speed);
      }
      if (event.key.keysym.sym == SDLK_s)
      {
        Speed speed = (Speed) {0, +MOVEMENT_SPEED};
        move_rect(surface, &pl1, &speed);
      }
    }
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(1);
  }
}
