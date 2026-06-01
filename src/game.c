#include "game.h"
#include "menus.h"
#include "raylib.h"
#include "raygui.h"
#include "raymath.h"

Font font;

GameState game;

Texture playerTex;
Texture obstacleTex;
Texture spyTex;

void InitGame(void) {
	InitWindow(ww, wh, "Cursed Dino");

	SetTargetFPS(fps);

  game.fCounter = 0;
  LoadScore();

  playerTex = LoadTexture("assets/dion.png");
  obstacleTex = LoadTexture("assets/llaw.png");
  spyTex = LoadTexture("assets/yps.png");

  LoadMenu();

  font = LoadFontEx("assets/funnyfont.ttf", 96, 0, 0);

  GuiSetFont(font);

  game.curScene = LOGO;
}

void UnloadGame(void) {
  UnloadTexture(playerTex);
  UnloadTexture(obstacleTex);
  UnloadTexture(spyTex);
  SaveScore();
}

void LoadScore(void) {
  int size;
  unsigned char *data = LoadFileData("assets/totallynothighscore", &size);
  
  if (size == sizeof(int)) {
    //int *intData = (int *)data;
    game.highScore = *((int *)data);

    TraceLog(LOG_INFO, "High score loaded succesfully.");
  }
  else {
    TraceLog(LOG_WARNING, "High score loaded succesfully.");
    game.highScore = 0;
  }

  UnloadFileData(data);
}

void SaveScore(void) {
  SaveFileData("assets/totallynothighscore", &game.highScore, sizeof(int));
}

Rectangle player = (Rectangle){60, 0, 30, 30};
Rectangle obstacle[2] = {(Rectangle){0, 0, 60, 200}, (Rectangle){0, wh - 200, 60, 200}};
Rectangle spy = (Rectangle){0, 0, 30, 30};

void StartGame() {
  game.fCounter = 0;

  player.y = 240;

  obstacle[0].x = ww;
  obstacle[1].x = ww + GetRandomValue(0, 120); //just some magic numbers to add randomness
  spy.x = ww + GetRandomValue(0, 150); 
  spy.y = GetRandomValue(0, ww - spy.height);

  game.curScene = GAME;
}

static bool spyUp = false;
static const int obstacleSpd = 4;
static const int spySpd = 3;
static const int spyFalSpd = 7;

void UpdateGame(void) {
  game.fCounter++;	
  game.points = game.fCounter / 60;

  if (IsKeyDown(KEY_SPACE)) player.y = Clamp(player.y - 5.0, 0, player.y);
  else player.y = Clamp(player.y + 3.0, player.y, wh - player.height);

  if (obstacle[0].x < -60) {
    obstacle[0].x = ww + GetRandomValue(0, 120);
  }

  if (obstacle[1].x < -60) {
    obstacle[1].x = ww + GetRandomValue(0, 120);
  }

  float pointsSpeed = game.points / 10.0; // added to speeds to increase difficulty
  float obstacleSpdTotal = obstacleSpd + pointsSpeed;

  obstacle[0].x -= obstacleSpdTotal;
  obstacle[1].x -= obstacleSpdTotal;

  if (game.points > 40) {
    spy.x -= spySpd + pointsSpeed;
    if (spy.x < 0 - spy.width) spy.x = ww + GetRandomValue(0, 150);

    if (spy.y > wh - spy.height || spy.y < 0) spyUp = !spyUp; //changes the direction of spy when he hits map boudary

    spy.y += spyUp ? -spyFalSpd : spyFalSpd;

    if (CheckCollisionRecs(player, spy)) goto ded;
  }

  if (CheckCollisionRecs(player, obstacle[0]) || CheckCollisionRecs(player, obstacle[1])) {
  ded:
    if (game.highScore < game.points) game.highScore = game.points;
    game.curScene = END;
  }
}

bool OnWindow(Rectangle rec) {
  if (CheckCollisionRecs(rec, (Rectangle){0, 0, ww, wh})) return true;
  else return false;
}

void DrawGame(void) {
  GuiLabel((Rectangle){0, 0, ww, 100}, TextFormat("Points: %d\nFly with SPACE.", game.points));

  if (OnWindow(player)) DrawTexture(playerTex, player.x, player.y, WHITE);
  if (OnWindow(obstacle[0])) DrawTexture(obstacleTex, obstacle[0].x, obstacle[0].y, WHITE);
  if (OnWindow(obstacle[1])) DrawTexture(obstacleTex, obstacle[1].x, obstacle[1].y, WHITE);
  if (OnWindow(spy)) DrawTexture(spyTex, spy.x, spy.y, WHITE);
}
