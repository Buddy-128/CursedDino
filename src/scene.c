#include "scene.h"

//local
#include "game.h"

//the ray stuff
#include "raylib.h"
#include "raymath.h"

void 
LoadScene(Scene scene)
{
  switch (scene)
  {
    case SCENE_MENU:
      //LoadMenu()
    break;
    case SCENE_GAME:
      //LoadGame()
  }
}

void 
UnloadScene(Scene scene)
{
  switch (scene)
  {
    case SCENE_MENU:
      //UnloadMenu()
    break;
    case SCENE_GAME:
      //UnloadGame()
  }
}

void 
UpdateScene(Scene scene, double step)
{
  switch (scene)
  {
    case SCENE_MENU:
      //UpdateMenu()
    break;
    case SCENE_GAME:
      //UpdateGame()
  }
}

void 
DrawScene(Scene scene)
{
  switch (scene)
  {
    case SCENE_MENU:
      //DrawMenu()
    break;
    case SCENE_GAME:
      //DrawGame()
  }
}

float opacity;
bool updateTransition = false;
bool fadeOut;

void 
TransToScene(Scene scene)
{
  opacity = 0;
  updateTransition = true;

  fadeOut = true;

  LoadScene(scene);

  Scene oldCurScene = GetCurScene();

  UnloadScene(oldCurScene);

  SetCurScene(scene);

  fadeOut = false;

  updateTransition = false;
}

void
UpdateTransition(double step)
{
  if (updateTransition)
  {
    if (fadeOut)
    {
      opacity = Clamp(0, 1.0, opacity + 0.1 * step);
    }
    else
    {
      opacity = Clamp(0, 1.0, opacity - 0.1 * step);
    }
  }
}

void
DrawTransition(void)
{
  Vector2 res = GetWindowRes();
  DrawRectangle(0, 0, res.x, res.y, Fade(BLACK, opacity));
}
