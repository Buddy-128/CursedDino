#include "scene.h"

//local
#include "game.h"
#include "menus.h"
#include "dino.h"

//the ray stuff
#include "raylib.h"
#include "raymath.h"

void 
LoadScene(Scene scene)
{
  switch (scene)
  { //when i wrote this i relaized that my scene manager absolutely sucks in this game
    case SCENE_LOGO:
      LoadMenu();
    break;
    /*case SCENE_MENU:
      LoadMenu();
    break;*/
    case SCENE_DINO:
      LoadDino();
    break;
    /*case SCENE_END:
      LoadMenu();
    break;*/
  }
}

void 
UnloadScene(Scene scene)
{
  switch (scene)
  {
    case SCENE_DINO:
      UnloadDino();
  }
}

void 
UpdateScene(Scene scene, double step)
{
  switch (scene)
  {
    case SCENE_LOGO:
      UpdateLogo(step);
    break;
    case SCENE_DINO:
      UpdateDino(step);
  }
}

void 
DrawScene(Scene scene)
{
  switch (scene)
  {
    case SCENE_LOGO:
      DrawLogo();
    break;
    case SCENE_MENU:
      DrawMenu();
    break;
    case SCENE_DINO:
      DrawDino();
    break;
    case SCENE_END:
      DrawEnd();
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
