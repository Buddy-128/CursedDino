#include "raylib.h"

typedef enum GameScreen { LOGO = 0, MENU, SELECT, CH1, ENDLESS, LOSE, WIN, END} GameScreen;

int main(void) 
{
	float playerY = 240;
	float obstacleX = 640;
	float obstacle1X = 760;

	int frameCounter = 0;
	int points = 0;
	int gameState = 0;
	int ptTextX;
	
	Vector2 spyPos = {940, 451};

	bool close = false;
	bool spyUp = false;

	GameScreen currentScreen = LOGO;

	Color btColor0 = GREEN;
	Color btColor1 = GREEN;
	Color btColor2 = GREEN;
	Color btColor3 = GREEN;
	Color btColor4 = GREEN;
	Color btColor5 = GREEN;
	Color btColor6 = GREEN;
	Color btColor7 = GREEN;
	Color btColor8 = GREEN;
	
	InitWindow(640, 480, "Cursed Dino");

	SetTargetFPS(60);

	void StartGame(int type) 
	{
		gameState = 0;
		frameCounter = 0;

		playerY = 240;

		obstacleX = 640;
		obstacle1X = 760;
		spyPos.x = 940; 
		spyPos.y = 451;

		if (type == 0) 
		{
			currentScreen = ENDLESS;
		}
		else if (type == 1) 
		{
			currentScreen = CH1;
		}
        	
	}


	/*place for loading textures and stuff (trust me this is the only place)*/

	Texture2D dino = LoadTexture("assets/dion.png");
	Texture2D wall = LoadTexture("assets/llaw.png");
	Texture2D yps = LoadTexture("assets/yps.png");

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

		/*for SELECT*/
		Rectangle Button4 = {230, 200, 180, 60};
		Rectangle Button5 = {230, 280, 180, 60};
		Rectangle Button6 = {260, 360, 120, 60};

		bool onbt4 = CheckCollisionRecs(cursor, Button4);
		bool onbt5 = CheckCollisionRecs(cursor, Button5);
		bool onbt6 = CheckCollisionRecs(cursor, Button6);

		/*for ENDLESS and CH1*/
		Rectangle player = {120, playerY, 30, 30};
		Rectangle spy = {(float)spyPos.x, (float)spyPos.y, 29, 20};
        Rectangle obstacle = {obstacleX, 280, 60, 200};
		Rectangle obstacle1 = {obstacle1X, 0, 60, 200};

    	bool collision = CheckCollisionRecs(player, obstacle);
		bool collision1 = CheckCollisionRecs(player, obstacle1);
		bool collision2 = CheckCollisionRecs(player, spy);
		
		/*for WIN and LOSE (they share this)*/
		Rectangle Button2 = {260, 220, 120, 60};
		Rectangle Button3 = {260, 300, 120, 60};
			
		bool onbt2 = CheckCollisionRecs(cursor, Button2);
		bool onbt3 = CheckCollisionRecs(cursor, Button3);

		/*for END*/
		Rectangle Button7 = {260, 220, 120, 60};
		Rectangle Button8 = {260, 300, 120, 60};
			
		bool onbt7 = CheckCollisionRecs(cursor, Button7);
		bool onbt8 = CheckCollisionRecs(cursor, Button8);


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
						currentScreen = SELECT;
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

			case SELECT:
			{	
				if (onbt4) {
					btColor4 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						StartGame(0);
					}	
				}
				else {
					btColor4 = GREEN;
				}

				if (onbt5) {
					btColor5 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						StartGame(1);
					}	
				}
				else {
					btColor5 = GREEN;
				}

				if (onbt6) {
					btColor6 = DARKGREEN;

					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						currentScreen = MENU;
					}	
				}
				else {
					btColor6 = GREEN;
				}
			}break;

			case CH1: 
			{
				frameCounter++;

	       			if (IsKeyDown(KEY_SPACE)) {playerY -= 5.0f;}
				else {playerY += 3.0f;}
      
               			obstacleX -= 8.0f;
				obstacle1X -= 8.0f;
     
    			        if (obstacleX < -60) {obstacleX = 640;}

				if (obstacle1X < -60) {obstacle1X = 760;}

				if (playerY < 0) {playerY = 0;}

				if (playerY > 450) {playerY = 450;}

        			if (collision || collision1 || collision2) {gameState = 2;}

				if (spyPos.y > 460) {
					spyUp = true;
				}
				else if (spyPos.y < 0) {
					spyUp = false;
				}

				if (spyUp) {
					spyPos.y -= 7.0f;
				}
				else {
					spyPos.y += 7.0f;
				}

				spyPos.x -= 3.0f;

				if (spyPos.x < -29) {spyPos.x = 940;}
				
					
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

			case ENDLESS :
			{
				frameCounter++;	
				points = frameCounter / 60;
	       			
				if (IsKeyDown(KEY_SPACE)) {playerY -= 5.0f;}
				else {playerY += 3.0f;}
      
     
    			        if (obstacleX < -60) {obstacleX = 640;}

				if (obstacle1X < -60) {obstacle1X = 760;}

				if (playerY < 0) {playerY = 0;}

				if (playerY > 450) {playerY = 450;}

        			if (collision || collision1) {gameState = 2;}

				if (frameCounter > 1200 && frameCounter < 2400) {
        	       			obstacleX -= 6.0f;
					obstacle1X -= 6.0f;				
				}
				else if (frameCounter > 2400 && frameCounter < 3600){				
               				obstacleX -= 7.0f;
					obstacle1X -= 7.0f;
					spyPos.x -= 3.0f;
				}
				else if (frameCounter > 3600){				
               				obstacleX -= 10.0f;
					obstacle1X -= 10.0f;
					spyPos.x -= 5.0f;
				}			
				else {
					obstacleX -= 5.0f;
					obstacle1X -= 5.0f;
				}

				if (gameState == 2) {
					currentScreen = END;
				}

				if (spyPos.y > 460) {
					spyUp = true;
				}
				else if (spyPos.y < 0) {
					spyUp = false;
				}

				if (spyUp) {
					spyPos.y -= 7.0f;
				}
				else {
					spyPos.y += 7.0f;
				}


				if (spyPos.x < -29) {spyPos.x = 940;}
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

			case END:
			{
				if (onbt7) {
					btColor7 = DARKGREEN;
					
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						StartGame(0);
					}			
				}
				else {
					btColor7 = GREEN;
				}
				
				if (onbt8) {
					btColor8 = DARKGREEN;
					
					if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
						currentScreen = MENU;	
					}			
				}
				else {
					btColor8 = GREEN;
				}
				
				if (points > 10 && points < 100) {
					ptTextX = 115;
				}
				else if (points > 100) {
					ptTextX = 105;
				}
				else {
					ptTextX = 125;
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

			case SELECT:
			{	
				ClearBackground(SKYBLUE);
	        	DrawTextEx(font, "Which Gamemode?", (Vector2){155, 60}, 60, 0, BLACK);
	        	DrawRectangleRec(Button4, btColor4);
				DrawTextEx(font, "Endless", (Vector2){260, 207}, 40, 0, BLACK);
				DrawRectangleRec(Button5, btColor5);
				DrawTextEx(font, "Challenge", (Vector2){255, 287}, 40, 0, BLACK);
				DrawRectangleRec(Button6, btColor6);
				DrawTextEx(font, "Back", (Vector2){285, 367}, 40, 0, BLACK);			
			}break;

	 		case CH1: 
			{
				ClearBackground(SKYBLUE);
				DrawTextEx(font,"Fly with SPACE.", (Vector2){60, 60}, 20, 0, BLACK);
				DrawTexture(dino, (int)player.x, playerY, RAYWHITE);
				DrawTexture(wall, obstacleX, (int)obstacle.y, RAYWHITE);
				DrawTexture(wall, obstacle1X, (int)obstacle1.y, RAYWHITE);
				DrawTexture(yps, (int)spyPos.x, (int)spyPos.y, RAYWHITE);
	        }break;

	 		case ENDLESS: 
			{
				ClearBackground(SKYBLUE);
				DrawTextEx(font,"Fly with SPACE.", (Vector2){60, 60}, 20, 0, BLACK);
				DrawTextEx(font, TextFormat("Points: %d", points), (Vector2){60, 100}, 20, 0, BLACK);
				DrawTexture(dino, (int)player.x, playerY, RAYWHITE);
				DrawTexture(wall, obstacleX, (int)obstacle.y, RAYWHITE);
				DrawTexture(wall, obstacle1X, (int)obstacle1.y, RAYWHITE);
				DrawTexture(yps, (int)spyPos.x, (int)spyPos.y, RAYWHITE);
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

			case END:
			{	
				ClearBackground(SKYBLUE);
				DrawTextEx(font, TextFormat("YOUR SCORE IS %d!", points), (Vector2){ptTextX, 120}, 60, 0, DARKGREEN);
				DrawRectangleRec(Button7, btColor7);
	       		DrawTextEx(font, "Again", (Vector2){280, 227}, 40, 0, BLACK);	
				DrawRectangleRec(Button8, btColor8);
				DrawTextEx(font, "Menu", (Vector2){280, 307}, 40, 0, BLACK);	
			}break;
		}
	EndDrawing();
	}
	
	UnloadTexture(dino);
	UnloadTexture(wall);
	UnloadTexture(yps);
	UnloadFont(font);
	
	CloseWindow();
	
	return 0;
}