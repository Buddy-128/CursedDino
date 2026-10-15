#ifndef INIT_H_
#define INIT_H_

#include "raylib.h"
#include "scene.h"

typedef struct Game 
{
  Font font;
  float scale;
  Vector2 res;
  Scene curScene;
} Game;

void LoadGame(void);
void UnloadGame(void);

Font *GetGameFont(void);

float GetWindowScale(void);
Vector2 GetWindowRes(void);

Scene GetCurScene(void);
void SetCurScene(Scene next);

#endif
