#include <SDL2/SDL.h>
#include <stdio.h>

#define WHITE_COLOR 0xFFFFFFFF

static int MOVEMENT_SPEED = 2;

static int SURFACE_WIDTH = 640;
static int SURFACE_HEIGHT = 480;

static int LEFT_INNER_BORDER = 80;
static int RIGHT_INNER_BORDER = 560;
static int BOTTOM_INNER_BORDER = 480;
static int TOP_INNER_BORDER = 0;

static int BALL_DIAMETER = 20;

static int PLAYER_WIDTH = 40;
static int PLAYER_HEIGHT = 200;

typedef struct Speed {
  int x;
  int y;
} Speed;

typedef struct Score {
  int pl1;
  int pl2;
} Score;

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
void move_ball(SDL_Surface* surface, SDL_Rect* ball, SDL_Rect* pl1, SDL_Rect* pl2, Speed* ball_speed, Score* score)
{
  int player_hit = 0;

  //When hit Player 1 side
  if (ball->x <= LEFT_INNER_BORDER)
  {
    if ((ball->y + ball->h > pl1->y) && (ball->y < pl1->y + pl1->h))
    {
      ball_speed->x = -ball_speed->x;
      int ball_center_y = ((ball->y+ball->h/2));
      int player_center_y = ((pl1->y+pl1->h/2));
      double hit_fraction = ((double) ball_center_y - (double) player_center_y)/ ((double) PLAYER_HEIGHT) * 2;
      ball_speed->y = (double) (hit_fraction * (double) MOVEMENT_SPEED);
      player_hit = 1;
    }
    else 
    {
      score->pl2++;
    }
    
  }
  
  //When hit player 2 side
  if (ball->x + ball->w >= RIGHT_INNER_BORDER)
  {
    if ((ball->y + ball->h > pl2->y) && (ball->y < pl2->y + pl2->h))
    {
      ball_speed->x = -ball_speed->x;
      int ball_center_y = ((ball->y+ball->h/2));
      int player_center_y = ((pl2->y+pl2->h/2));
      double hit_fraction = ((double) ball_center_y - (double) player_center_y)/ ((double) PLAYER_HEIGHT) * 2;
      ball_speed->y = (double) (hit_fraction * (double) MOVEMENT_SPEED);
      player_hit = 1;
    }
    else 
    {
      score->pl1++;
    }
  }

  //Ball hit top or bottom border
  if(ball->y <= TOP_INNER_BORDER)
    ball_speed->y = -ball_speed->y;
  if(ball->y + ball->h >= BOTTOM_INNER_BORDER)
    ball_speed->y = -ball_speed->y;

  move_rect(surface, ball, ball_speed);
}

void draw_init_game(SDL_Surface* surface, Score* score, SDL_Rect* pl1, SDL_Rect* pl2, SDL_Rect* ball, Speed* ball_speed)
{
  SDL_Rect reset = (SDL_Rect) {0,0, SURFACE_WIDTH, SURFACE_WIDTH};
  SDL_FillRect(surface, &reset, 0x00000000); 
  //Draw Player 1
  *pl1 = (SDL_Rect) {LEFT_INNER_BORDER - PLAYER_WIDTH, SURFACE_HEIGHT/2 - PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_FillRect(surface, pl1, WHITE_COLOR);

  //Draw Player 2
  *pl2 = (SDL_Rect) {RIGHT_INNER_BORDER, SURFACE_HEIGHT/2 - PLAYER_HEIGHT/2, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_FillRect(surface, pl2, WHITE_COLOR);

  //Draw Ball
  *ball = (SDL_Rect) {(LEFT_INNER_BORDER + RIGHT_INNER_BORDER)/2, SURFACE_HEIGHT/2 - BALL_DIAMETER/2, BALL_DIAMETER, BALL_DIAMETER};
  SDL_FillRect(surface, ball, WHITE_COLOR);

  *ball_speed = (Speed) {MOVEMENT_SPEED, 0};
}

int main()
{
  //Init the window with SDL2
  SDL_InitSubSystem(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);

  Score score = (Score) {0,0};
  Speed ball_speed = (Speed) {MOVEMENT_SPEED, 0};

  //Init
  SDL_Rect pl1 = (SDL_Rect) {LEFT_INNER_BORDER - PLAYER_WIDTH, 300, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_Rect pl2 = (SDL_Rect) {RIGHT_INNER_BORDER, 100, PLAYER_WIDTH, PLAYER_HEIGHT};
  SDL_Rect ball = (SDL_Rect) {(LEFT_INNER_BORDER + RIGHT_INNER_BORDER)/2, 300, BALL_DIAMETER, BALL_DIAMETER};
  SDL_Rect border = (SDL_Rect) {320, 0, 1, 480};

  draw_init_game(surface, &score, &pl1, &pl2, &ball, &ball_speed);
  
  int running = 1;
  SDL_Event event;

  int local_pl1_score = 0;
  int local_pl2_score = 0;

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
    move_ball(surface, &ball, &pl1, &pl2, &ball_speed, &score);

    //Check if score chnaged
    int score_changed = 0;
    if (score.pl1 != local_pl1_score)
    {
      local_pl1_score = score.pl1;
      draw_init_game(surface, &score, &pl1, &pl2, &ball, &ball_speed);
      score_changed = 1;
    }
    if (score.pl2 != local_pl2_score)
    {
      local_pl2_score = score.pl2;
      draw_init_game(surface, &score, &pl1, &pl2, &ball, &ball_speed);
      score_changed = 1;
    }
    if (score_changed) 
    {
      printf("Score pl1 : %d\nScore pl2 : %d\n", score.pl1, score.pl2);
    }
    //Draw Border
    SDL_FillRect(surface, &border, WHITE_COLOR);
    
    //Update window
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
  }
}
