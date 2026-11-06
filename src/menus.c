#include "menus.h"

#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include "game.h"
#include "dino.h"

static MenuElements menu;

static double scale;
static Vector2 res;

static double timer;

static Vector2 textPos;

void LoadMenu(void) {
  scale = GetWindowScale();
  res = GetWindowRes();
  timer = 0;

  Vector2 btnSize = (Vector2){120 * scale, 60 * scale};
  menu.playBt = (Rectangle){0, 0, btnSize.x, btnSize.y};
  menu.quitBt = (Rectangle){0, 0, btnSize.x, btnSize.y};

  menu.playBt.x = (res.x - btnSize.x) / 2.0;
  menu.playBt.y = res.y / 2.0 - btnSize.y / 2.0;

  menu.quitBt.x = menu.playBt.x;
  menu.quitBt.y = 3 * res.y / 4.0 - btnSize.y / 2.0;

  textPos = Vector2Subtract((Vector2){res.x / 2.0, res.y / 2.0}, Vector2Divide(MeasureTextEx(GuiGetFont(), "</>", 20 * scale, 0), (Vector2){2.0, 2.0}));
}


void UpdateLogo(double step) {
  timer += step;

  if (timer >= 2) {
    timer = 0;
    TransToScene(SCENE_MENU);
  }
}

void DrawLogo(void) {
  DrawCircle(res.x / 2.0, res.y / 2.0, 60 * scale, BLACK);
  DrawTextEx(GuiGetFont(), "</>", textPos, 20 * scale, 0, PINK);

  //GuiSetStyle(DEFAULT, TEXT_SIZE, 30 * scale);
  GuiLabel((Rectangle){0, 320 * scale, res.x, 30 * scale}, "Buddy-128");
}

void DrawMenu(void) {
  GuiSetStyle(DEFAULT, TEXT_SIZE, 60 * scale);
  GuiLabel((Rectangle){0, 0, res.x, 180 * scale}, "Cursed Dino");
  GuiSetStyle(DEFAULT, TEXT_SIZE, 30 * scale);

  if (GuiButton(menu.playBt, "Play")) TransToScene(SCENE_DINO);
  else if (GuiButton(menu.quitBt, "Quit")) EndGame();
}

void DrawEnd(void) {
  GuiLabel((Rectangle){0, 0, res.x, 180 * scale}, TextFormat("YOUR SCORE IS %d!\nHigh score: %d", GetGameScore(), GetHighScore()));

  if (GuiButton(menu.playBt, "Again")) TransToScene(SCENE_DINO);
  else if (GuiButton(menu.quitBt, "Menu")) TransToScene(SCENE_MENU);
}
