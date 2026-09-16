#ifndef LOGO_H
#define LOGO_H

#include "asd.h"
#include "raylib.h"

void LoadLogoTexture(int load, int screenWidth);

void UpdateLogo(int screenWidth, int screenHeight, LogoPhase *phase, float scale, bool drawLogo);

void DrawLogo(int screenHeight);

#endif