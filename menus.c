#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include "game.h"
#include "menus.h"

static MenuElements menu;

//for LOGO
Vector2 windowHalfed = (Vector2){ww / 2.0, wh / 2.0};
Vector2 textPos;

void LoadMenu(void) {
  menu.playBt = (Rectangle){260, 240, 120, 60};
  menu.quitBt = (Rectangle){260, 320, 120, 60};

  GuiLoadStyle("assets/style_terminal.rgs");

  GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
  GuiSetStyle(DEFAULT, TEXT_SPACING, 0);
  GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 35);
  GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
  textPos = Vector2Subtract(windowHalfed, Vector2Divide(MeasureTextEx(GuiGetFont(), "</>", 20, 0), (Vector2){2.0, 2.0}));
}

void UpdateLogo(void) {
  game.fCounter++;

  if (game.fCounter == fps * 2) {
    game.curScene = MENU;
    game.fCounter = 0;
  }
}


void DrawLogo(void) {
  DrawCircleV(windowHalfed, 60, BLACK);
  DrawTextEx(font, "</>", textPos, 20, 0, PINK);

  GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
  GuiLabel((Rectangle){0, 320, ww, 30}, "Buddy-128");
}

void DrawMenu(void) {
  GuiSetStyle(DEFAULT, TEXT_SIZE, 60);
  GuiLabel((Rectangle){0, 0, ww, 180}, "Cursed Dino");
  GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

  if (GuiButton(menu.playBt, "Play")) StartGame();
  else if (GuiButton(menu.quitBt, "Quit")) game.close = true;
}

void DrawEnd(void) {
  GuiLabel((Rectangle){0, 0, ww, 180}, TextFormat("YOUR SCORE IS %d!\nHigh score: %d", game.points, game.highScore));

  if (GuiButton(menu.playBt, "Again")) StartGame();
  else if (GuiButton(menu.quitBt, "Menu")) game.curScene = MENU;
}
