#ifndef GAME_H_
#define GAME_H_

#include "raylib.h"

#define ww 640
#define wh 480
#define fps 60

typedef enum GameScene {LOGO = 0, MENU, GAME, END} GameScene;

typedef struct GameState {
  GameScene curScene;
  bool close;
  int points;
  int highScore;
  int fCounter;
} GameState;

extern Font font;

extern GameState game;

void InitGame(void);
void UnloadGame(void);
void StartGame(void);

void LoadScore(void);
void SaveScore(void);

void UpdateGame(void);
void DrawGame(void);

#endif
