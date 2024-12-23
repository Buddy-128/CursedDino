#include "raylib.h"

typedef enum GameScreen { LOGO = 0, MENU, SELECT, GAME, GAME1, LOSE, WIN} GameScreen;

int main(void) 
{
	float playerY = 240;
	float obstacleX = 640;
	float obstacle1X = 760;

	int frameCounter = 0;
	int gameState = 0;
	
	bool close = false;

	GameScreen currentScreen = LOGO;

	Color btColor0 = GREEN;
	Color btColor1 = GREEN;
	Color btColor2 = GREEN;
	Color btColor3 = GREEN;

	InitWindow(640, 480, "Cursed Dino");

	SetTargetFPS(60);

	void StartGame(int type) 
	{
		gameState = 0;
		frameCounter = 0;

		playerY = 240;

		obstacleX = 640;
		obstacle1X = 760;

		if (type == 1) {currentScreen = GAME;}
        	
	}


	/*place for loading textures and stuff (trust me this is the only place)*/

	Texture2D dino = LoadTexture("assets/dion.png");
	Texture2D wall = LoadTexture("assets/llaw.png");

	Font font = LoadFontEx("assets/funnyfont.ttf", 96, 0, 0);
	
	while(!WindowShouldClose()) 
	{
		if (close) {break;}
		
		/*for entire program*/
		Vector2 mousePos = GetMousePosition();
		Rectangle cursor = {(float)mousePos.x, (float)mousePos.y, 5, 5};
		
		/*for MENU*/
		Rectangle Button = {260, 220, 120, 60};
		Rectangle Button1 = {260, 300, 120, 60};

		bool onbt0 = CheckCollisionRecs(cursor, Button);
		bool onbt1 = CheckCollisionRecs(cursor, Button1);
		
		/*for GAME*/
		Rectangle player = {120, playerY, 30, 30};
               	Rectangle obstacle = {obstacleX, 280, 60, 200};
		Rectangle obstacle1 = {obstacle1X, 0, 60, 200};

       		bool collision = CheckCollisionRecs(player, obstacle);
		bool collision1 = CheckCollisionRecs(player, obstacle1);
		
		/*for WIN and LOSE (they share this)*/
		Rectangle Button2 = {260, 220, 120, 60};
		Rectangle Button3 = {260, 300, 120, 60};
			
		bool onbt2 = CheckCollisionRecs(cursor, Button2);
		bool onbt3 = CheckCollisionRecs(cursor, Button3);	


		/* this switch function is made for the logic of the game */
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
				if (onbt0) {
					btColor0 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						StartGame(1);
					}	
				}
				else {
					btColor0 = GREEN;
				}

				if (onbt1) {
					btColor1 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						close = true;
					}
				}
				else {
					btColor1 = GREEN;
				}
			}break;

			case GAME: 
			{
				frameCounter++;

	       			if (IsKeyDown(KEY_SPACE)) {playerY -= 5.0f;}
				else {playerY += 3.0f;}
      
               			obstacleX -= 5.0f;
				obstacle1X -= 5.0f;
     
    			        if (obstacleX < -60) {obstacleX = 640;}

				if (obstacle1X < -60) {obstacle1X = 760;}

				if (playerY < 0) {playerY = 0;}

				if (playerY > 450) {playerY = 450;}

        			if (collision || collision1) {gameState = 2;}

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
				if (onbt2) {
					btColor2 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						StartGame(1);
					}	
				}
				else {
					btColor2 = GREEN;
				}

				if (onbt3) {
					btColor3 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						currentScreen = MENU;
					}
				}
				else {
					btColor3 = GREEN;
				}

			}break;

			case LOSE: 
			{
				if (onbt2) {
					btColor2 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						StartGame(1);
					}	
				}
				else {
					btColor2 = GREEN;
				}

				if (onbt3) {
					btColor3 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						currentScreen = MENU;
					}
				}
				else {
					btColor3 = GREEN;
				}
			}break;
		}

	BeginDrawing();
		/* this is the switch case made just for RENDERING! */
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
	        	DrawRectangleRec(Button, btColor0);
			DrawTextEx(font, "Play", (Vector2){290, 227}, 40, 0, BLACK);
			DrawRectangleRec(Button1, btColor1);
			DrawTextEx(font, "Quit", (Vector2){290, 307}, 40, 0, BLACK);


		}break;

	 	case GAME: 
		{
			ClearBackground(SKYBLUE);
			DrawTextEx(font,"Fly with SPACE.", (Vector2){60, 60}, 20, 0, BLACK);
			DrawTexture(dino, (int)player.x, playerY, RAYWHITE);
			DrawTexture(wall, obstacleX, (int)obstacle.y, RAYWHITE);
			DrawTexture(wall, obstacle1X, (int)obstacle1.y, RAYWHITE);

	        }break;

	        case WIN: 
		{
	       		ClearBackground(SKYBLUE);
			DrawTextEx(font, "YOU WON!!!", (Vector2){195, 120}, 60, 0, GOLD);
			DrawRectangleRec(Button2, btColor2);
	       		DrawTextEx(font, "Again", (Vector2){280, 227}, 40, 0, BLACK);
			DrawRectangleRec(Button3, btColor3);
			DrawTextEx(font, "Menu", (Vector2){280, 307}, 40, 0, BLACK);

	    	}break;

	    	case LOSE: 
		{
			ClearBackground(SKYBLUE);
			DrawTextEx(font, "YOU LOST!!!", (Vector2){195, 120}, 60, 0, RED);
			DrawRectangleRec(Button2, btColor2);
	       		DrawTextEx(font, "Again", (Vector2){280, 227}, 40, 0, BLACK);	
			DrawRectangleRec(Button3, btColor3);
			DrawTextEx(font, "Menu", (Vector2){280, 307}, 40, 0, BLACK);
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
