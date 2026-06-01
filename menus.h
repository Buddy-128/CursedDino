#ifndef MENUS_H_
#define MENUS_H_

typedef struct MenuElements {
  //MENU
  Rectangle playBt;
  Rectangle quitBt;
} MenuElements;

void LoadMenu(void);

void UpdateLogo(void);
void DrawLogo(void);

void DrawMenu(void);

void DrawEnd(void);
#endif
