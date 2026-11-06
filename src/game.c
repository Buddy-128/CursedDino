#include "game.h"

#include <stddef.h>

#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define FONT_SIZE 60 // the font size loaded (i set it to the highest font size used in game)
#define FONT_GLYPH_AMOUNT 256

#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 320

Game GAME;

void 
LoadGame(void) 
{
  SetConfigFlags(FLAG_VSYNC_HINT);
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  //SetTraceLogLevel(LOG_ERROR);

  InitWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Cursed Dino");
  InitAudioDevice();

  int monitor = GetCurrentMonitor();

  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);

  ToggleFullscreen();
  SetWindowSize(width, height);

  GAME.res = (Vector2){width, height};

  GAME.scale = height / DEFAULT_HEIGHT;

  GAME.font = LoadFontEx("assets/funnyfont.ttf", FONT_SIZE * GAME.scale, NULL, FONT_GLYPH_AMOUNT);
  SetTextureFilter(GAME.font.texture, TEXTURE_FILTER_TRILINEAR);

  GuiLoadStyle("assets/style_terminal.rgs");

  GuiSetFont(GAME.font);
  GuiSetStyle(DEFAULT, TEXT_SIZE, 30 * GAME.scale);
  GuiSetStyle(DEFAULT, TEXT_SPACING, 3 * GAME.scale);
  GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 35 * GAME.scale);
  GuiSetStyle(DEFAULT, BORDER_WIDTH, 2 * GAME.scale);
  GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

  //load and switch to the first scene
  LoadScene(SCENE_LOGO);
  SetCurScene(SCENE_LOGO);
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

void
EndGame(void)
{
  GAME.end = true;
}

bool
ShouldGameEnd(void)
{
  return GAME.end;
}

//score funcs 
void LoadScore(void) {
  int size;
  unsigned char *data = LoadFileData("assets/totallynothighscore", &size);
  
  if (size == sizeof(int)) {
    GAME.highScore = *((int *)data);

    TraceLog(LOG_INFO, "High score loaded succesfully.");
  }
  else {
    TraceLog(LOG_WARNING, "High score loaded a wrong type. Resetting the highScore.");
    GAME.highScore = 0;
  }

  UnloadFileData(data);
}

void SaveScore(int score) {
  SaveFileData("assets/totallynothighscore", &score, sizeof(int));
  GAME.highScore = score;
}

int GetHighScore(void)
{
  return GAME.highScore;
}
