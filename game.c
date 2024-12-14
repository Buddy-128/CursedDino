/* known bugs:  bad positioning of texts, finish the game */

/* my dreams: finished working game, endless mode, local coop or versus mode?? */


#include "raylib.h"

typedef enum GameScreen { LOGO = 0, MENU, GAME, LOSE, WIN} GameScreen;

int main(void) 
{
	const int screenWidth = 640;
	const int screenHeight = 480;

	float playerY = screenHeight/2;
	float obstacleX = screenWidth;
	float obstacle1X = screenWidth + 120;

	int frameCounter = 0;
	int gameState = 0;
   
	bool collision;
	bool collision1;

	GameScreen currentScreen = LOGO;

	InitWindow(screenWidth, screenHeight, "game");

	SetTargetFPS(60);


	/*place for loading textures and stuff (trust me this is the only place)*/

	Texture2D dino = LoadTexture("assets/dion.png");
	Texture2D wall = LoadTexture("assets/llaw.png");

	Font font = LoadFontEx("assets/funnyfont.ttf", 96, 0, 0);
	
	while(!WindowShouldClose()) 
	{
		switch(currentScreen) 
		{
			case LOGO: 
			{
				frameCounter++;

				if(frameCounter > 120) {
					currentScreen = MENU;
				}
			}break;

			case MENU: 
			{
				if(IsKeyDown(KEY_ENTER)) {
					gameState = 0;
					playerY = screenHeight/2;
					obstacleX = screenWidth;
					obstacle1X = screenWidth + 120;
					frameCounter = 0;
					currentScreen = GAME;
				}
			}break;

			case GAME: 
			{
				frameCounter++;

				if(frameCounter > 1800) {
					gameState = 1;
				}

				if(gameState == 2) {
					currentScreen = LOSE;
				}
				if(gameState == 1) {
					currentScreen = WIN;
				}
			}break;

			case WIN: 
			{
				if(IsKeyDown(KEY_ENTER)) {
					gameState = 0;
					playerY = screenHeight/2;
					obstacleX = screenWidth;
					obstacle1X = screenWidth + 120;
					frameCounter = 0;
					currentScreen = GAME;
				}
			}break;

			case LOSE: 
			{
				if(IsKeyDown(KEY_ENTER)) {
					gameState = 0;
					playerY = screenHeight/2;
					obstacleX = screenWidth;
					obstacle1X = screenWidth + 120;
					frameCounter = 0;
					currentScreen = GAME;
				}
			}break;
		}

	BeginDrawing();
		switch(currentScreen) {
       		case LOGO: 
		{
			ClearBackground(SKYBLUE);
			DrawCircle(307, 172, 60, BLACK);
	                DrawTextEx(font,"</>", (Vector2){295, 160} , 20, 0, PINK);
	        	DrawTextEx(font,"Buddyhoslav_", (Vector2){235, 340} , 30, 0, RAYWHITE);
	 	}break;
	    
	 	case MENU: 
	  	{
			ClearBackground(SKYBLUE);
	        	DrawTextEx(font, "Cursed Dino 2", (Vector2){155, 60}, 60, 0, DARKGREEN);
	        	DrawTextEx(font, "Press ENTER to play!", (Vector2){155, 240}, 40, 0, BLACK);
		}break;

	 	case GAME: 
		{
	       		Rectangle player = {120, playerY, 30, 30};
               		Rectangle obstacle = {obstacleX, 280, 60, 200};
			Rectangle obstacle1 = {obstacle1X, 0, 60, 200};
       			collision = CheckCollisionRecs(player, obstacle);
			collision1 = CheckCollisionRecs(player, obstacle1);

       			if (IsKeyDown(KEY_SPACE)) {playerY -= 5.0f;}
			else {playerY += 3.0f;}
      
               		obstacleX -= 5.0f;
			obstacle1X -= 5.0f;
     
    		        if (obstacleX < -60) {obstacleX=screenWidth;}

			if (obstacle1X < -60) {obstacle1X=screenWidth + 120;}

			if (playerY < 0) {playerY = 0;}

			if (playerY > 450) {playerY = 450;}

        		if (collision || collision1) {gameState = 2;}

	       		ClearBackground(SKYBLUE);
			DrawTextEx(font,"Fly with SPACE.", (Vector2){60, 60}, 20, 0, BLACK);
			DrawTexture(dino, (int)player.x, (int)player.y, RAYWHITE);
			DrawTexture(wall, (int)obstacle.x, (int)obstacle.y, RAYWHITE);
			DrawTexture(wall, (int)obstacle1.x, (int)obstacle1.y, RAYWHITE);

	        }break;

	        case WIN: 
		{
			ClearBackground(SKYBLUE);

	        	DrawTextEx(font, "YOU WON!!!", (Vector2){200, 120}, 60, 0, GOLD);
	       		DrawTextEx(font, "Press ENTER to play again or ESCAPE to quit.", (Vector2){150, 240}, 20, 0, BLACK);
	    	}break;

	    	case LOSE: 
			{
			ClearBackground(SKYBLUE);

	       		DrawTextEx(font, "YOU LOST!!!", (Vector2){195, 120}, 60, 0, RED);
	       		DrawTextEx(font, "Press ENTER to play again or ESCAPE to quit.", (Vector2){150, 240}, 20, 0, BLACK);
	    	}break;
	}
	EndDrawing();
	}

	UnloadTexture(dino);
	UnloadTexture(wall);
	UnloadFont(font);
    
	CloseWindow();
	return 0;
}
