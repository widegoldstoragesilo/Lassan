#include "st.h"
#include "asd.h"
#include "raylib.h"

#define ST_BUTTON_COUNT (sizeof(stButtons) / sizeof(stButtons[0]))

typedef struct Buttons {
    Rectangle rect;
    Texture2D icon;
} Button;

Button stButtons[1];

void LoadSTButtons(int load, int screenWidth, int screenHeight)
{
    if (load == 0)
    {
        stButtons[0].icon = LoadTexture("resources/quit_Icon.png");
    }

    else if (load == 1)
    {
        for (int i = 0; i < ST_BUTTON_COUNT; i++) UnloadTexture(stButtons[i].icon);
    }
}

void UpSTButtons(int screenWidth, int screenHeight, float scale)
{
    stButtons[0].rect = (Rectangle){ screenWidth * 0.9f - 18 * scale * 0.8, screenHeight * 0.1f - 18 * scale * 0.8, 36 * scale * 0.8, 36 * scale * 0.8};
}

static bool wasHoveredst[ST_BUTTON_COUNT] = { false };

void UpdateSTScreen(GameScreen *currentScreen, int *langue, int screenWidth, int screenHeight, float scale)
{
    Vector2 mouse = GetMousePosition();

        for (int i = 0; i < ST_BUTTON_COUNT; i++)
        {
            bool isHoveredM = CheckCollisionPointRec(mouse, stButtons[i].rect);

            if (isHoveredM && !wasHoveredst[i])
            {
                stButtons[i].rect.width   *= 1.2f;
                stButtons[i].rect.height  *= 1.2f;
                stButtons[i].rect.x   -= (stButtons[i].rect.width - (stButtons[i].rect.width / 1.2f)) / 2 ;
                stButtons[i].rect.y   -= (stButtons[i].rect.height - (stButtons[i].rect.height / 1.2f)) / 2;
            }
            else if (!isHoveredM && wasHoveredst[i])
            {
                stButtons[i].rect.width   /= 1.2f;
                stButtons[i].rect.height  /= 1.2f;
                stButtons[i].rect.x   += ((stButtons[i].rect.width * 1.2f) - stButtons[i].rect.width) / 2;
                stButtons[i].rect.y   += ((stButtons[i].rect.height * 1.2f) - stButtons[i].rect.height) / 2;
            }
            wasHoveredst[i] = isHoveredM;

            if (CheckCollisionPointRec(mouse, stButtons[i].rect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                if (i == 0) *currentScreen = MENU;
                /*if (i == 1) ;
                if (i == 2) ;
                if (i == 3) ; */
            }
        }
}
void DrawSTScreen()
{
    for (int i = 0; i < ST_BUTTON_COUNT; i++)
        {
            Rectangle stSource = { 0, 0, (float)stButtons[i].icon.width, (float)stButtons[i].icon.height };

            DrawTexturePro(stButtons[i].icon, stSource, stButtons[i].rect, (Vector2){ 0, 0 }, 0.0f, WHITE);
        }
}
