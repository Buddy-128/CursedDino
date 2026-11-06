#ifndef SCENE_H_
#define SCENE_H_

typedef enum Scene {SCENE_LOGO, SCENE_MENU, SCENE_DINO, SCENE_END} Scene;

void LoadScene(Scene scene);
void UnloadScene(Scene scene);
void UpdateScene(Scene scene, double step);
void DrawScene(Scene scene);

void TransToScene(Scene scene);

void UpdateTransition(double step);
void DrawTransition(void);

#endif
