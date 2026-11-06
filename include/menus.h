#ifndef MENUS_H_
#define MENUS_H_

#include "raylib.h"

typedef struct MenuElements {
  //MENU
  Rectangle playBt;
  Rectangle quitBt;
} MenuElements;

void LoadMenu(void);

void UpdateLogo(double step);
void DrawLogo(void);

void DrawMenu(void);

void DrawEnd(void);
#endif
