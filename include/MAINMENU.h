#ifndef MAINMENU_h
#define MAINMENU_h

#include "raylib.h"
#include "raymath.h"

#include "PROPERTIES.h"

namespace Menu
{
    int mouseHooverMen = -1;
    
    static Texture2D newgame_butt,savedgame_butt,BG_HomeScreen;
    Rectangle button[2] = {{125, 500, 447, 65},{125, 600, 447, 64}};
    
    void LoadMenuTexture()
    {
        newgame_butt = LoadTexture("./resource/NEWGAME_button.png");
        savedgame_butt = LoadTexture("./resource/SAVEDGAME_button.png");
        BG_HomeScreen = LoadTexture("./resource/IMG_0307.png");
    }

    void UnLoadMenuTexture()
    {
        UnloadTexture(newgame_butt);
        UnloadTexture(savedgame_butt);
    }

    void DrawMenu()
    {
        ClearBackground(Assets::DarkPurple);
        DrawTexture(BG_HomeScreen, 0, 0, WHITE);
        
        LoadMenuTexture();
        
        for (int i = 0 ; i < 2 ; ++i)
        {
            if (CheckCollisionPointRec(GetMousePosition(), button[i]))
            {
                if (i == 1 && SaveFileValid == 0) mouseHooverMen = -1;
                else
                {
                    mouseHooverMen = i;
                    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                    {
                        if (i == 0) currentScreen = difficulty;
                        else currentScreen = savedgame;
                    }
                    break; // important!
                }
            }
            else mouseHooverMen = -1;
        }
        
        DrawTexture(newgame_butt, button[0].x, button[0].y,(mouseHooverMen == 0) ? GRAY : WHITE);
        if (SaveFileValid) DrawTexture(savedgame_butt, button[1].x, button[1].y,(mouseHooverMen == 1) ? GRAY : WHITE);
        
        //UnLoadMenuTexture();
    }
}

#endif
