#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>

#define WHITE_COLOR 0xFFFFFFFF

static int MOVEMENT_SPEED = 10;

static int LEFT_INNER_BORDER = 80;
static int RIGHT_INNER_BORDER = 560;

static int PLAYER_WIDTH = 40;
static int PLAYER_HEIGHT = 200;

typedef struct Speed {
  int x;
  int y;
} Speed;

void move_rect(SDL_Surface* surface, SDL_Rect* rect, Speed* speed)
{
  SDL_FillRect(surface, rect, 0x00000000);
  rect->x += speed->x;
  rect->y += speed->y;
  SDL_FillRect(surface, rect, WHITE_COLOR);
}

/* direction is 1 or -1 */
void move_player(SDL_Surface* surface, SDL_Rect* pl,int direction)
{
  if(pl->y <= 0 && -1 == direction)
    return;
  if (pl->y >= surface->h - pl->h && 1 == direction)
    return;
  Speed speed = (Speed) {0,direction*MOVEMENT_SPEED};
  move_rect(surface, pl ,&speed);
}

void move_ball(SDL_Surface* surface, SDL_Rect* ball, SDL_Rect* pl1, SDL_Rect* pl2, Speed* ball_speed)
{
  if (ball->x < LEFT_INNER_BORDER)
    ball_speed->x = -ball_speed->x;
  if (ball->x + ball->w > RIGHT_INNER_BORDER)
    ball_speed->x = -ball_speed->x;

  move_rect(surface, ball, ball_speed);
}

int main()
{
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  
  SDL_Rect pl1 = (SDL_Rect) {LEFT_INNER_BORDER - PLAYER_WIDTH, 40, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_FillRect(surface, &pl1, WHITE_COLOR);

  SDL_Rect pl2 = (SDL_Rect) {RIGHT_INNER_BORDER, 120, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_FillRect(surface, &pl2, WHITE_COLOR);

  SDL_Rect ball = (SDL_Rect) {320, 240, 10,10};
  SDL_FillRect(surface, &ball, WHITE_COLOR);
  Speed ball_speed = (Speed) {10, 0};

  SDL_Rect border = (SDL_Rect) {320, 0, 1, 480};

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
        move_player(surface, &pl1, -1);
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        move_player(surface, &pl1, 1);
      }
      
      if (event.key.keysym.sym == SDLK_z)
      {
        move_player(surface, &pl2, -1);
      }
      if (event.key.keysym.sym == SDLK_s)
      {
        move_player(surface, &pl2, 1);
      }
    }

    //move ball
    move_ball(surface, &ball, &pl1, &pl2, &ball_speed);
   
    //Draw Border
    SDL_FillRect(surface, &border, WHITE_COLOR);
    
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
  }
}
