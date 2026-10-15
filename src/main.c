#include "raylib.h"

#include "game.h"
#include "scene.h"

int 
main() 
{
  LoadGame();

  const double step = 1 / 60.0;
  double accu = 0; //accumulator that caps update at 60FPS

	while(!WindowShouldClose()){
    float dt = GetFrameTime();
    if (dt > .25) dt = .25; //prevents game break if FPS small
    
    accu += dt;

    for (;accu >= step;) {
      //update here and pass step
      UpdateScene(GetCurScene(), step);

      UpdateTransition(step);
      accu -= step;
    }

		BeginDrawing();
      ClearBackground(BLACK);

      DrawScene(GetCurScene());
      
      DrawTransition();
		EndDrawing();
	}

  UnloadGame();
	return 0;
}
