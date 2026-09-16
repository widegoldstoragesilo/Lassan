#include "raylib.h"
#include "menu.h"
#include "asd.h"

#define MENU_BUTTON_COUNT (sizeof(menuButtons) / sizeof(menuButtons[0]))
#define LANGUE_BUTTON_COUNT (sizeof(langueButtons) / sizeof(langueButtons[0]))

typedef struct Buttons {
    Rectangle rect;
    Texture2D icon;
} Button;


Button menuButtons[4];

void LoadMenuButtons(int load, int screenWidth, int screenHeight)
{
    if (load == 0)
    {
        menuButtons[0].icon = LoadTexture("resources/playE_Icon.png");
        menuButtons[1].icon = LoadTexture("resources/st_Icon.png");
        menuButtons[2].icon = LoadTexture("resources/costume_Icon.png");
        menuButtons[3].icon = LoadTexture("resources/quit_Icon.png");
    }

    else if (load == 1)
    {
        for (int i = 0; i < MENU_BUTTON_COUNT; i++) UnloadTexture(menuButtons[i].icon);
    }
}

void UpMenuButtons(int screenWidth, int screenHeight, float scale)
{
    menuButtons[0].rect = (Rectangle){ screenWidth * 0.5f - 30 * scale, screenHeight / 8 * 7 - 30 * scale, 60 * scale, 36 * scale };
    menuButtons[1].rect = (Rectangle){ screenWidth * 0.9f - 18 * scale, screenHeight * 0.4f - 18 * scale, 36 * scale, 36 * scale };
    menuButtons[2].rect = (Rectangle){ screenWidth * 0.9f - 18 * scale, screenHeight * 0.6f - 18 * scale, 36 * scale, 36 * scale };
    menuButtons[3].rect = (Rectangle){ screenWidth * 0.9f - 18 * scale * 0.8, screenHeight * 0.1f - 18 * scale * 0.8, 36 * scale * 0.8, 36 * scale * 0.8};
}


Button langueButtons[2];

void LoadlangueButton(int load, int screenWidth, int screenHeight)
{
    if (load == 0)
    {
        langueButtons[0].icon = LoadTexture("resources/langueEN_Icon.png");
        langueButtons[1].icon = LoadTexture("resources/langueHU_Icon.png");
    }
    
    else if (load == 1)
    {
        for (int i = 0; i < LANGUE_BUTTON_COUNT; i++) UnloadTexture(langueButtons[i].icon);
    }
}

void UpLangueButtons(int screenWidth, int screenHeight, float scale)
{
    langueButtons[0].rect = (Rectangle){ screenWidth * 0.1f - 18 * scale, screenHeight * 0.1f - 12 * scale, 36 * scale, 24 * scale };
    langueButtons[1].rect = (Rectangle){ screenWidth * 0.1f - 18 * scale, screenHeight * 0.1f - 12 * scale, 36 * scale, 24 * scale };
}

static bool wasHoveredM[MENU_BUTTON_COUNT] = { false };
static bool wasHoveredL[LANGUE_BUTTON_COUNT] = { false };

void UpdateMENUScreen(GameScreen *currentScreen, int *langue, int screenWidth, int screenHeight, float scale, bool drawMButtons)
{
    Vector2 mouse = GetMousePosition();

    if (drawMButtons)
    {
        for (int i = 0; i < MENU_BUTTON_COUNT; i++)
        {
            bool isHoveredM = CheckCollisionPointRec(mouse, menuButtons[i].rect);

            if (isHoveredM && !wasHoveredM[i])
            {
                menuButtons[i].rect.width   *= 1.2f;
               menuButtons[i].rect.height  *= 1.2f;
               menuButtons[i].rect.x   -= (menuButtons[i].rect.width - (menuButtons[i].rect.width / 1.2f)) / 2 ;
               menuButtons[i].rect.y   -= (menuButtons[i].rect.height - (menuButtons[i].rect.height / 1.2f)) / 2;
            }
            else if (!isHoveredM && wasHoveredM[i])
            {
               menuButtons[i].rect.width   /= 1.2f;
                menuButtons[i].rect.height  /= 1.2f;
                menuButtons[i].rect.x   += ((menuButtons[i].rect.width * 1.2f) - menuButtons[i].rect.width) / 2;
               menuButtons[i].rect.y   += ((menuButtons[i].rect.height * 1.2f) - menuButtons[i].rect.height) / 2;
            }
            wasHoveredM[i] = isHoveredM;

            if (CheckCollisionPointRec(mouse, menuButtons[i].rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 0) *currentScreen = GAME;
                if (i == 1) *currentScreen = ST;
                if (i == 2) *currentScreen = CUST;
                if (i == 3) CloseWindow();
            }
        }
    
        for (int i = 0; i < LANGUE_BUTTON_COUNT; i++)
        {
            bool isHoveredL = CheckCollisionPointRec(mouse, langueButtons[i].rect);

            if (isHoveredL && !wasHoveredL[i])
            {
                langueButtons[i].rect.width     *= 1.2f;
                langueButtons[i].rect.height    *= 1.2f;
                langueButtons[i].rect.x -= (langueButtons[i].rect.width - (langueButtons[i].rect.width / 1.2f)) / 2 ;
                langueButtons[i].rect.y -= (langueButtons[i].rect.height - (langueButtons[i].rect.height / 1.2f)) / 2 ;
            }
            else if (!isHoveredL && wasHoveredL[i])
            {
                langueButtons[i].rect.width     /= 1.2f;
                langueButtons[i].rect.height    /= 1.2f;
                langueButtons[i].rect.x += ((langueButtons[i].rect.width * 1.2f) - langueButtons[i].rect.width) / 2;
                langueButtons[i].rect.y += ((langueButtons[i].rect.height * 1.2f) - langueButtons[i].rect.height) / 2;
            }
            wasHoveredL[i] = isHoveredL;
        }

        if (CheckCollisionPointRec(mouse, langueButtons[*langue].rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                *langue = (*langue == 0) ? 1 : 0;
            }
    }
}

void DrawMENUScreen(int langue, bool drawMButtons)
{
    if (drawMButtons)
    {
        for (int i = 0; i < MENU_BUTTON_COUNT; i++)
        {
            Rectangle menuSource = { 0, 0, (float)menuButtons[i].icon.width, (float)menuButtons[i].icon.height };

            DrawTexturePro(menuButtons[i].icon, menuSource, menuButtons[i].rect, (Vector2){ 0, 0 }, 0.0f, WHITE);
        }

        Rectangle langueSource = { 0, 0, (float)langueButtons[langue].icon.width, (float)langueButtons[langue].icon.height };

        DrawTexturePro(langueButtons[langue].icon, langueSource, langueButtons[langue].rect, (Vector2){ 0, 0 }, 0.0f, WHITE);

        DrawText(TextFormat("Btn0 width: %.2f", menuButtons[0].rect.width), 10, 170, 20, WHITE);
    }
}