#include "raylib.h"
#include "logo.h"
#include <math.h>

typedef enum LogoPhase {SLIDING_IN, FLOATING } LogoPhase;

static float slideSpeed = 300.0f;
static float floatTimer = 0;
static float degeneration = 0;

Texture2D logoTexture;
static Vector2 logoPos;
static Rectangle logoRect;


void LoadLogoTexture(int load)
{
    if (load == 0)
    {
        logoTexture = LoadTexture("resources/logo.png");
        logoPos = (Vector2){ 0, -100 };
    }
    
    else if (load == 1)
    {
        UnloadTexture(logoTexture);
    }
}
    

void UpdateLogo(int screenWidth, int screenHeight, Rectangle logoRect, LogoPhase *phase, float scale)
{
    float logoWidth = 150 * scale * 2;
    float logoHeight = 100 * scale * 2;
    float dt = GetFrameTime();
    
    if (IsWindowResized())
    {
        logoPos.x = screenWidth / 2 - logoWidth / 2 ;
    }

    if (*phase == SLIDING_IN)
    {
        degeneration = (slideSpeed * slideSpeed) / (2.0f * (screenHeight / 8) - logoPos.y);

        slideSpeed -= degeneration * dt;
        if (slideSpeed < 0) slideSpeed = 0;

        logoPos.y += slideSpeed * dt;

        if (logoPos.y >= screenHeight / 8)
        {
            logoPos.y = screenHeight / 8;
            *phase = FLOATING;
        }
    }
    else if (*phase == FLOATING)
    {
        floatTimer += dt;
        logoPos.y = screenHeight / 8 + sinf(floatTimer * 1.5f) * 20.0f;
    }
}

void DrawLogo(Rectangle logoRect)
{
    //DrawTextureEx(logoTexture, logoPos, 0, 1, WHITE);
    Rectangle source = { 0, 0, (float)logoTexture.width, (float)logoTexture.height };
    DrawTexturePro(logoTexture, source, logoRect, (Vector2){ 0, 0 }, 0.0f, WHITE);
}