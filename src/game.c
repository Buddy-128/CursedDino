#include "game.h"

#include <stddef.h>

#include "raylib.h"

#define FONT_SIZE 150 // the font size loaded (i set it to the highest font size used in game)
#define FONT_GLYPH_AMOUNT 256

#define DEFAULT_WIDTH 1920
#define DEFAULT_HEIGHT 1080

Game GAME;

void 
LoadGame(void) 
{
  SetConfigFlags(FLAG_VSYNC_HINT);
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  //SetTraceLogLevel(LOG_ERROR);

  InitWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "example project");
  InitAudioDevice();

  GAME.font = LoadFontEx("assets/font.ttf", FONT_SIZE, NULL, FONT_GLYPH_AMOUNT);

  int monitor = GetCurrentMonitor();

  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);

  ToggleFullscreen();
  SetWindowSize(width, height);

  GAME.res = (Vector2){width, height};

  GAME.scale = height / DEFAULT_HEIGHT;

  //load and switch to the first scene
  LoadScene(SCENE_MENU);
  SetCurScene(SCENE_MENU);
}

void
UnloadGame() 
{
  //unload the current scene
  UnloadScene(GetCurScene());

  UnloadFont(GAME.font);
  CloseAudioDevice();
  CloseWindow();
}

//font
Font
*GetGameFont(void)
{
  return &GAME.font;
}

//scale
float 
GetWindowScale(void) 
{
  return GAME.scale;
}

//resolution
Vector2
GetWindowRes(void)
{
  return GAME.res;
}

//Scenes
Scene
GetCurScene(void) 
{
  return GAME.curScene;
}

void 
SetCurScene(Scene next) 
{
  GAME.curScene = next;
}

