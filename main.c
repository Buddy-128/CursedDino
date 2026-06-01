#include "raylib.h"

#include "game.h"
#include "menus.h"
#include "ch.h"

int main(void) {
  InitGame();

	while (!WindowShouldClose()) {
		if (game.close) break;
		
		switch(game.curScene){
			case LOGO: 
        UpdateLogo();
			break;
			case GAME:
        UpdateGame();
      break;
      default:
    }

    BeginDrawing();
      ClearBackground(SKYBLUE);
      switch(game.curScene) {
        case LOGO: 
          DrawLogo();
        break;
        case MENU: 
          DrawMenu();
        break;
        case GAME:
          DrawGame();
        break;
        case END:
          DrawEnd();
        break;
        default:
      }
    EndDrawing();
	}
	
  UnloadGame();
	
	CloseWindow();
	
	return 0;
}
