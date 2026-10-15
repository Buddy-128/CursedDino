#ifndef SCENE_H_
#define SCENE_H_

typedef enum Scene {SCENE_MENU, SCENE_GAME} Scene;

void LoadScene(Scene scene);
void UnloadScene(Scene scene);
void UpdateScene(Scene scene, double step);
void DrawScene(Scene scene);

void TransitionToScene(Scene scene);

void UpdateTransition(double step);
void DrawTransition(void);

#endif
