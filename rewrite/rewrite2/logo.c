#include "raylib.h"
#include "logo.h"
#include <math.h>
#include "asd.h"


Texture2D logoTexture;
static Vector2 logoPos;
static Rectangle logoRect;

void LoadLogoTexture(int load, int screenWidth)
{
    if (load == 0)
    {
        logoTexture = LoadTexture("resources/logo.png");
        logoPos = (Vector2){ screenWidth / 2.0f - 150, -150 };
    }
    else if (load == 1)
    {
        UnloadTexture(logoTexture);
    }
}

static float slideSpeed = 300;
static float floatTimer = 0;
static float degeneration = 0;

void UpdateLogo(int screenWidth, int screenHeight, LogoPhase *phase, float scale, bool drawLogo)
{
    float logoWidth = 150 * scale;
    float logoHeight = 100 * scale;
    float dt = GetFrameTime();

    logoPos.x = screenWidth / 2.0f - logoWidth / 2.0f;

    if (!drawLogo) logoPos.y = -logoHeight;

    if (*phase == SLIDING_IN && drawLogo)
    {
        slideSpeed -= (slideSpeed * slideSpeed) / (2.0f * ((screenHeight / 8) - logoPos.y)) * dt;

        //if (slideSpeed < 1) slideSpeed = 0.9;
        logoPos.y += slideSpeed * dt;

        if (logoPos.y >= screenHeight / 8.0f || 0.05 > (screenHeight / 8) - logoPos.y)
        {
            //logoPos.y = screenHeight / 8.0f;
            *phase = FLOATING;
        }
    }
    else if (*phase == FLOATING)
    {
        floatTimer += dt;
        logoPos.y = screenHeight / 8.0f + sinf(floatTimer * 1.5f) * 15.0f * scale;
    }
    logoRect = (Rectangle){ logoPos.x, logoPos.y, logoWidth, logoHeight };
}

void DrawLogo(int screenHeight)
{
    Rectangle source = { 0, 0, (float)logoTexture.width, (float)logoTexture.height };
    DrawTexturePro(logoTexture, source, logoRect, (Vector2){ 0, 0 }, 0.0f, WHITE);

    DrawText(TextFormat("Logo: %.3f", logoPos.y - (screenHeight / 8)), 10, 90, 20, YELLOW);
    DrawText(TextFormat("Slidespeed: %.3f", slideSpeed), 10, 150, 20, YELLOW);
}