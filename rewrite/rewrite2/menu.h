#ifndef MENU_H
#define MENU_H

void UpdateMENUScreen(GameScreen *currentScreen, int *langue, int screenWidth, int screenHeight, float scale, bool drawMButtons);
void DrawMENUScreen(int langue, bool drawMButtons);

void LoadMenuButtons(int load, int screenWidth, int screenHeight);
void UpMenuButtons(int screenWidth, int screenHeight, float scale);

void LoadlangueButton(int load, int screenWidth, int screenHeight); //struct langueButtons *buttons);
void UpLangueButtons(int screenWidth, int screenHeight, float scale);

#endif