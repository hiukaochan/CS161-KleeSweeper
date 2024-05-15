#ifndef WINLOSE_h
#define WINLOSE_h

#include "PROPERTIES.h"
#include "raylib.h"

#include <string>

namespace wlscreen
{
    static Texture2D win_screen, lose_screen, WL_menu, WL_again;
    Rectangle wlbutton[2] = {{334,600,256,61},{690,600,256,61}};
    int mouseHooverWL;

    void PlayAgainPress()
    {
        x_click = 0; y_click = 0; cntopen = 0; cntflag = CurrCell.mines; Timer = 0.0; FrameCount = 0; is_count_frame = false;
        GameStatus = true;
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                is_Flaged[i][j] = false;
                is_Open[i][j] = false;
                is_Bomb[i][j] = false;
            }
        }
        currentScreen = gameplay;
    }

    void MainMenuPress()
    {
        x_click = 0; y_click = 0; cntopen = 0; Timer = 0.0; FrameCount = 0;
        GameStatus = true;
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                is_Flaged[i][j] = false;
                is_Open[i][j] = false;
                is_Bomb[i][j] = false;
            }
        }
        CurrCell = {10,10,30};
        currentScreen = mainmenu;
    }

    void LoadallTexture()
    {
        win_screen = LoadTexture("./resource/WL_win.png");
        lose_screen = LoadTexture("./resource/WL_lose.png");
        WL_menu = LoadTexture("./resource/WL_mainmenu.png");
        WL_again = LoadTexture("./resource/WL_playagain.png");
    }

    void UnloadallTexture()
    {
        UnloadTexture(win_screen);
        UnloadTexture(lose_screen);
        UnloadTexture(WL_menu);
        UnloadTexture(WL_again);
    }

    void DrawScreen()
    {
        
        if (GameStatus) DrawTexture(win_screen,0,0,WHITE);
        else DrawTexture(lose_screen, 0, 0, WHITE);
        
        DrawTexture(WL_menu, 334, 600, WHITE);
        DrawTexture(WL_again, 690, 600, WHITE);
        
        if (GameStatus)
        {
            int text_size = MeasureText(TextFormat("Win with time spent: %03.02f", Timer), 30);
            DrawText(TextFormat("Win with time spent: %03.02f", Timer), 640 - text_size/2, 510, 30, Assets::RedText);
            
            text_size = MeasureText(TextFormat("Fastest win on %02ix%02i with %02i mines: %03.02f", CurrCell.rows, CurrCell.cols, CurrCell.mines, BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}]), 30);
            DrawText(TextFormat("Fastest win on %01ix%01i with %01i mines: %03.02f", CurrCell.rows, CurrCell.cols, CurrCell.mines, BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}]), 640 - text_size/2, 550, 30, Assets::RedText);
        }
        else
        {
            int text_size = MeasureText(TextFormat("Time spent: %03.02f", Timer), 30);
            DrawText(TextFormat("Time spent: %03.02f", Timer), 640 - text_size/2, 510, 30, Assets::RedText);
            if (BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}] != 0.0)
            {
                text_size = MeasureText(TextFormat("Fastest win on %02ix%02i with %02i mines: %03.02f", CurrCell.rows, CurrCell.cols, CurrCell.mines, BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}]), 30);
                DrawText(TextFormat("Fastest win on %01ix%01i with %01i mines: %03.02f", CurrCell.rows, CurrCell.cols, CurrCell.mines, BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}]), 640 - text_size/2, 550, 30, Assets::RedText);
            }
            else
            {
                text_size = MeasureText(TextFormat("No record of fastest win on %01ix%01i with %01i mines", CurrCell.rows, CurrCell.cols, CurrCell.mines), 30);
                DrawText(TextFormat("No record of fastest win on %01ix%01i with %01i mines", CurrCell.rows, CurrCell.cols, CurrCell.mines), 640 - text_size/2, 550, 30, Assets::RedText);
            }
        }
        
        for (int i = 0 ; i < 2 ; ++i) 
        {
            if (CheckCollisionPointRec(GetMousePosition(), wlbutton[i]))
            {
                mouseHooverWL = i;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    if (i == 1) PlayAgainPress();
                    else MainMenuPress();
                }
                break; // important!
            }
            else mouseHooverWL = -1;
        }
        
        for (int i = 0; i < 2; ++i)
        {
            Texture2D b_new;
            if (i==0) b_new = WL_menu;
            else b_new = WL_again;
            DrawTexture(b_new, wlbutton[i].x, wlbutton[i].y,(mouseHooverWL == i) ? GRAY : WHITE);
        }
        
        //UnloadallTexture();
        
    }
}

#endif
