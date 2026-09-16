#include "raylib.h"
#include <math.h>
#include "logo.h"
#include "menu.h"
//#include "ls.h"
#include "asd.h"
#include "st.h"
//#include "game.h"

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(void)
{
    // window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    int screenWidth = 800;
    int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Lassan!");
    SetTargetFPS(60);
    //texture buttons idk
    int load = 0;
    LoadMenuButtons(load, screenWidth, screenHeight);
    LoadlangueButton(load, screenWidth, screenHeight);
    LoadLogoTexture(load, screenWidth);
    LoadSTButtons(load, screenWidth, screenHeight);
    // player
    /*float size = 20;
    float moveSpeed = 400.0f;
    Vector2 position = { screenWidth / 2 - ( size / 2 ) , screenHeight / 7 * 4 };
    // player v
    Vector2 velocity = { 0, 0 };
    float gravity = 2500.0f;
    float jumpForce = -700.0f;
    float fastFallMultiplier = 5.0f;
    bool isOnGround = false; */
    // wall v
    bool isTouchingWall = false;
    int wallJumpCount = 0;
    int maxWallJumps = 8;
    float wallJumpCooldown = 1.2f;
    float wallJumpCooldownTimer = 0.0f;
    bool wallJumpLocked = false;
    float wallJumpJump = -700.0f;
    //screen
    //typedef enum GameScreen { MENU, LS, ST, GAME } GameScreen; // LCD-Loading sCreen LS-Level Select ST-SetThings 
    GameScreen currentScreen = MENU;
    //typedef enum LogoPhase { SLIDING_IN, FLOATING } LogoPhase;
    LogoPhase logoPhase = SLIDING_IN;
    
    //leangue
    int langue = 0;
    //scale up
    float scale = screenWidth * 0.003;

    UpMenuButtons(screenWidth, screenHeight, scale);
    UpLangueButtons(screenWidth, screenHeight, scale);
    UpSTButtons(screenWidth, screenHeight, scale);
    // timer
    static float timer;
    static bool drawLogo = false;
    static bool drawMButtons = false;


    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        timer += dt;

        if (IsWindowResized())
        {
            UpMenuButtons(screenWidth, screenHeight, scale);
            UpLangueButtons(screenWidth, screenHeight, scale);
            UpSTButtons(screenWidth, screenHeight, scale);
        }

        if (timer > 1) drawLogo = true;
        if (timer > 5) drawMButtons = true;

        if (IsWindowResized())
        {
            screenWidth = GetScreenWidth();
            screenHeight = GetScreenHeight();

            float scaleW = screenWidth * 0.003;
            float scaleH = screenHeight * 0.003;
            
            if (scaleW > scaleH) scale = scaleW;
            else if (scaleH > scaleW) scale = scaleH;

            if (scaleW < scaleH) scale = scaleW;
            else if (scaleH < scaleW) scale = scaleH;
        }


        switch (currentScreen)
        {
            case MENU:     UpdateMENUScreen(&currentScreen, &langue, screenWidth, screenHeight, scale, drawMButtons); break;
            case LS: /*UpdateLSScreen(&currentScreen, &langue, screenWidth, screenHeight, scale);*/ break;
            case ST:  UpdateSTScreen(&currentScreen, &langue, screenWidth, screenHeight, scale); break;
            //case GAME:  UpdateGameScreen(); break;
        }
    
        if (currentScreen == MENU)
        {
            UpdateLogo(screenWidth, screenHeight, &logoPhase, scale, drawLogo);
        }

        BeginDrawing();
        //ClearBackground(RAYWHITE);
        DrawRectangleGradientEx( (Rectangle){ 0, 0, screenWidth, screenHeight }, (Color){ 2, 51, 0, 255 }, (Color){ 26, 36, 7, 255 }, (Color){ 51, 21, 15, 255  }, (Color){ 26, 36, 7, 255 } );
        switch (currentScreen)
        {
            case MENU:     DrawMENUScreen(langue, drawMButtons); break;
            case LS: /*DrawLSScreen(langue);*/ break;
            case ST:  DrawSTScreen(); break;
            //case GAME:  DrawGameScreen(); break;
        }

        if (currentScreen == MENU)
        {
            DrawLogo(screenHeight);
        }


        DrawFPS(10, 10);
        DrawText(TextFormat("Scale: %.3f", scale), 10, 30, 20, YELLOW);
        DrawText(TextFormat("ScreenH: %.3f", screenHeight), 10, 50, 20, YELLOW);
        DrawText(TextFormat("ScreenW: %.3f", screenWidth), 10, 70, 20, YELLOW);

        DrawText(TextFormat("dt: %.3f", dt), 10, 110, 20, YELLOW);
        DrawText(TextFormat("timer: %.3f", timer), 10, 130, 20, YELLOW);

        EndDrawing();
    }

    load = 1;
    //unloads loads
    LoadMenuButtons(load, screenWidth, screenHeight);
    LoadlangueButton(load, screenWidth, screenHeight);
    LoadLogoTexture(load, screenWidth);
    LoadSTButtons(load, screenWidth, screenHeight);

    CloseWindow();
    return 0;
}