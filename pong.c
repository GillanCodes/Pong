#include <SDL2/SDL.h>

#define WHITE_COLOR 0xFFFFFFFF

static int MOVEMENT_SPEED = 2;

static int LEFT_INNER_BORDER = 80;
static int RIGHT_INNER_BORDER = 560;
static int BOTTOM_INNER_BORDER = 640;
static int TOP_INNER_BORDER = 0;

static int BALL_DIAMETER = 20;

static int PLAYER_WIDTH = 40;
static int PLAYER_HEIGHT = 200;

typedef struct Speed {
  int x;
  int y;
} Speed;

//Handle rectengle drawing
void move_rect(SDL_Surface* surface, SDL_Rect* rect, Speed* speed)
{
  SDL_FillRect(surface, rect, 0x00000000);
  rect->x += speed->x;
  rect->y += speed->y;
  SDL_FillRect(surface, rect, WHITE_COLOR);
}
// Handle player movement
/* direction is 1 or -1 */
void move_player(SDL_Surface* surface, SDL_Rect* pl,int direction)
{
  if(pl->y <= 0 && -1 == direction)
    return;
  if (pl->y >= surface->h - pl->h && 1 == direction)
    return;
  Speed speed = (Speed) {0,direction*MOVEMENT_SPEED*10};
  move_rect(surface, pl ,&speed);
}

// Handle Ball mouvement
void move_ball(SDL_Surface* surface, SDL_Rect* ball, SDL_Rect* pl1, SDL_Rect* pl2, Speed* ball_speed)
{
  //When hit Player 1 side
  if (ball->x <= LEFT_INNER_BORDER)
  {
    if ((ball->y + ball->h > pl1->y) && (ball->y < pl1->y + pl1->h))
    {
      ball_speed->x = -ball_speed->x;
      double hit_fraction = ((double) (ball->y+ball->h)/(double)2 - (double)(pl1->y+pl1->h)/(double)2)/((double)PLAYER_HEIGHT/2);
      ball_speed->y = (double) (hit_fraction * (double) MOVEMENT_SPEED);
    }  
  }
  
  //When hit player 2 side
  if (ball->x + ball->w >= RIGHT_INNER_BORDER)
  {
    if ((ball->y + ball->h > pl2->y) && (ball->y < pl2->y + pl2->h))
    {
      ball_speed->x = -ball_speed->x;
      double hit_fraction = ((double) (ball->y+ball->h)/(double)2 - (double)(pl2->y+pl2->h)/(double)2)/((double)PLAYER_HEIGHT/2);
      ball_speed->y = (double) (hit_fraction * (double) MOVEMENT_SPEED);
    }
  }

  //Ball hit top or bottom
  if(ball->y <= TOP_INNER_BORDER)
    ball_speed->y = -ball_speed->y;
  if(ball_speed->y + ball->h >= BOTTOM_INNER_BORDER)
    ball_speed->y = -ball_speed->y;
  move_rect(surface, ball, ball_speed);
}

int main()
{
  //Init the window with SDL2
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);
  
  //Init Player 1
  SDL_Rect pl1 = (SDL_Rect) {LEFT_INNER_BORDER - PLAYER_WIDTH, 40, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_FillRect(surface, &pl1, WHITE_COLOR);

  //Init Player 2
  SDL_Rect pl2 = (SDL_Rect) {RIGHT_INNER_BORDER, 10, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_FillRect(surface, &pl2, WHITE_COLOR);

  //Init Ball
  SDL_Rect ball = (SDL_Rect) {(LEFT_INNER_BORDER + RIGHT_INNER_BORDER)/2, 10, BALL_DIAMETER, BALL_DIAMETER};
  SDL_FillRect(surface, &ball, WHITE_COLOR);
  Speed ball_speed = (Speed) {MOVEMENT_SPEED, 0};

  //Init Border
  SDL_Rect border = (SDL_Rect) {320, 0, 1, 480};

  int running = 1;
  SDL_Event event;

  // Running loop
  while (running)
  {
    SDL_PollEvent(&event);
    // Quit listener
    if (event.type == SDL_QUIT)
    {
      running = 0;
    }

    //Input listener
    if (event.type == SDL_KEYDOWN)
    {
      //Player 2 mouvements
      if (event.key.keysym.sym == SDLK_UP)
      {
        move_player(surface, &pl2, -1);
      }
      if (event.key.keysym.sym == SDLK_DOWN)
      {
        move_player(surface, &pl2, 1);
      }
      //Player 1 mouvements
      if (event.key.keysym.sym == SDLK_z)
      {
        move_player(surface, &pl1, -1);
      }
      if (event.key.keysym.sym == SDLK_s)
      {
        move_player(surface, &pl1, 1);
      }
    }

    //move ball
    move_ball(surface, &ball, &pl1, &pl2, &ball_speed);
   
    //Draw Border
    SDL_FillRect(surface, &border, WHITE_COLOR);
    
    //Update window
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
  }
}
