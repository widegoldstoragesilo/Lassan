#ifndef ST_H
#define ST_H

void UpdateSTScreen(GameScreen *currentScreen, int *langue, int screenWidth, int screenHeight, float scale);
void DrawSTScreen();

void LoadSTButtons(int load, int screenWidth, int screenHeight);
void UpSTButtons(int screenWidth, int screenHeight, float scale);

#endif