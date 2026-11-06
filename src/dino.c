#include "dino.h"

#include "game.h"
#include "scene.h"
#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#define OBSTACLE_AMOUNT 2

static double scale;
static Vector2 res;

static Rectangle player;
static Texture playerTex;

static Rectangle obstacle[OBSTACLE_AMOUNT];
static Texture obstacleTex;
static const float obstacleSpd = 4;

static Rectangle spy;
static Texture spyTex;

static bool spyUp;
static const float spySpd = 3;
static const float spyFalSpd = 7;

static double timer;

static int score;

int GetGameScore(void)
{
  return score;
}

void LoadDino() {
  scale = GetWindowScale();
  res = GetWindowRes();

  player = (Rectangle){60 * scale, 240 * scale, 30 * scale, 30 * scale};
  playerTex = LoadTexture("assets/dion.png");

  obstacle[0] = (Rectangle){res.x, -60 * scale, 60 * scale, 200 * scale};

  obstacle[1] = (Rectangle){res.x + GetRandomValue(0, 120) * scale,
                            res.y - 140 * scale, 60 * scale, 200 * scale};

  obstacleTex = LoadTexture("assets/llaw.png");

  spy = (Rectangle){res.x + GetRandomValue(0, 150) * scale, 0, 30 * scale, 30 * scale};
  spy.y = GetRandomValue(0, res.y - spy.height);

  spyTex = LoadTexture("assets/yps.png");

  spyUp = false;

  timer = 0;
}

void UnloadDino(void)
{
  UnloadTexture(playerTex);
  UnloadTexture(obstacleTex);
  UnloadTexture(spyTex);
}

void UpdateDino(double step) {
  timer += step;
  score = (int)timer;

  if (IsKeyDown(KEY_SPACE)) player.y = Clamp(player.y - 4.0 * scale, 0, player.y);
  else player.y = Clamp(player.y + 2.0 * scale, player.y, res.y - player.height);

  if (obstacle[0].x < -60 * scale) {
    obstacle[0].x = res.x + GetRandomValue(0, 120) * scale;
  }

  if (obstacle[1].x < -60 * scale) {
    obstacle[1].x = res.x + GetRandomValue(0, 120) * scale;
  }

  float pointsSpeed = score / 10.0; // added to speeds to increase difficulty
  float obstacleSpdTotal = obstacleSpd * scale + pointsSpeed;

  obstacle[0].x -= obstacleSpdTotal;
  obstacle[1].x -= obstacleSpdTotal;

  if (score > 40) {
    spy.x -= (spySpd + pointsSpeed) * scale;
    if (spy.x < 0 - spy.width) spy.x = res.x + GetRandomValue(0, 150) * scale;

    if (spy.y > res.y - spy.height || spy.y < 0) spyUp = !spyUp; //changes the direction of spy when he hits map boudary

    spy.y += spyUp ? -spyFalSpd * scale : spyFalSpd * scale;

    if (CheckCollisionRecs(player, spy)) goto ded;
  }

  if (CheckCollisionRecs(player, obstacle[0]) || CheckCollisionRecs(player, obstacle[1])) {
  ded:
    if (GetHighScore() < score)
    {
      SaveScore(score);
    }

    TransToScene(SCENE_END);
  }
}

bool OnWindow(Rectangle rec) {
  if (CheckCollisionRecs(rec, (Rectangle){0, 0, res.x, res.y})) return true;
  else return false;
}

void DrawDino(void) {
  GuiLabel((Rectangle){0, 0, res.x, 100 * scale}, TextFormat("Points: %d\nFly with SPACE.", score));

  if (OnWindow(player)) DrawTextureEx(playerTex, (Vector2){player.x, player.y}, 0, scale, WHITE);
  if (OnWindow(obstacle[0])) DrawTextureEx(obstacleTex, (Vector2){obstacle[0].x, obstacle[0].y}, 0, scale, WHITE);
  if (OnWindow(obstacle[1])) DrawTextureEx(obstacleTex, (Vector2){obstacle[1].x, obstacle[1].y}, 0, scale, WHITE);
  if (OnWindow(spy)) DrawTextureEx(spyTex, (Vector2){spy.x, spy.y}, 0, scale, WHITE);
}
