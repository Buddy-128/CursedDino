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
  int highScore;
  bool end;
} Game;

void LoadGame(void);
void UnloadGame(void);

Font *GetGameFont(void);

float GetWindowScale(void);
Vector2 GetWindowRes(void);

Scene GetCurScene(void);
void SetCurScene(Scene next);

void LoadScore(void);
void SaveScore(int score);
int GetHighScore(void);

void EndGame(void);
bool ShouldGameEnd(void);

#endif
