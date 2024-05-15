#ifndef DIFFICULTY_h
#define DIFFICULTY_h

#include "raylib.h"
#include "raymath.h"

#include "PROPERTIES.h"
#include "WINLOSE.h"

namespace diff
{
    static Texture2D diff_BG, diff_ez, diff_med, diff_hard, diff_start, diff_menu, diff_leftarr, diff_rightarr;
    Rectangle button[11] = {{150,180,271,148}, {505,180,271,148}, {860,180,271,148}, {600,490,32,31}, {600,535,32,31}, {600,580,32,31}, {774,490,32,31}, {774,535,32,31}, {774,580,32,31}, {600,625,206,42},{464,725,352,65}};
    int mouseHooverDiff;

    void LoadallTexture()
    {
        diff_BG = LoadTexture("./resource/DIFF_bg.png");
        diff_ez = LoadTexture("./resource/DIFF_ez.png");
        diff_med = LoadTexture("./resource/DIFF_med.png");
        diff_hard = LoadTexture("./resource/DIFF_hard.png");
        diff_start = LoadTexture("./resource/DIFF_startbut.png");
        diff_menu = LoadTexture("./resource/DIFF_mainmenu.png");
        diff_leftarr = LoadTexture("./resource/DIFF_leftarr.png");
        diff_rightarr = LoadTexture("./resource/DIFF_rightarr.png");
    }

    void diff_UnloadTexture()
    {
        UnloadTexture(diff_BG);
        UnloadTexture(diff_ez);
        UnloadTexture(diff_med);
        UnloadTexture(diff_hard);
        UnloadTexture(diff_start);
        UnloadTexture(diff_menu);
        UnloadTexture(diff_leftarr);
        UnloadTexture(diff_rightarr);
    }

    void DrawDiff()
    {
        DrawTexture(diff_BG, 0, 0, WHITE);
        for (int i = 0; i < 11; ++i)
        {
            if (CheckCollisionPointRec(GetMousePosition(), button[i]))
            {
                mouseHooverDiff = i;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    switch (i)
                    {
                        case 0:
                        case 1:
                        case 2:
                        {
                            CurrCell.rows = defaultrow[i];
                            CurrCell.cols = defaultcol[i];
                            CurrCell.mines = defaultmine[i];
                            cntflag = CurrCell.mines;
                            wlscreen::PlayAgainPress();
                            break;
                        }
                        case 3: { if (CurrCell.rows > MIN_ROW) --CurrCell.rows; break; }
                        case 4: { if (CurrCell.cols > MIN_COL) --CurrCell.cols; break; }
                        case 5: { if (CurrCell.mines > MIN_MINE) --CurrCell.mines; break; }
                        case 6: { if (CurrCell.rows < MAX_ROW) ++CurrCell.rows; break; }
                        case 7: { if (CurrCell.cols < MAX_COL) ++CurrCell.cols; break; }
                        case 8: { if (CurrCell.mines < (CurrCell.rows*CurrCell.cols -1) ) ++CurrCell.mines; break; }
                        case 9: { cntflag = CurrCell.mines; currentScreen = gameplay; wlscreen::PlayAgainPress(); break; }
                        case 10: { currentScreen = mainmenu; break; }
                    }
                }
                break;
            }
            else mouseHooverDiff = -1;
        }
        
        for (int i = 0; i < 11; ++i)
        {
            Texture2D b_new;
            switch (i)
            {
                case 0: { b_new = diff_ez; break;}
                case 1: { b_new = diff_med; break;}
                case 2: { b_new = diff_hard; break;}
                case 3:
                case 4:
                case 5:
                    { b_new = diff_leftarr; break; }
                case 6:
                case 7:
                case 8: 
                    { b_new = diff_rightarr; break; }
                case 9: { b_new = diff_start; break; }
                case 10: { b_new = diff_menu; break; }
            }
            DrawTexture(b_new, button[i].x, button[i].y, (mouseHooverDiff == i) ? GRAY : WHITE);
        }
        
        if (CurrCell.mines > (CurrCell.rows*CurrCell.cols)-1) CurrCell.mines = (CurrCell.rows*CurrCell.cols)-1;
        
        int row_size = MeasureText(TextFormat("%02i",CurrCell.rows), 35);
        DrawText(TextFormat("%02i",CurrCell.rows), 705 - (row_size/2), 490 , 35, Assets::Diff_Brown);
        int col_size = MeasureText(TextFormat("%02i",CurrCell.cols), 35);
        DrawText(TextFormat("%02i",CurrCell.cols), 705 - (col_size/2), 535 , 35, Assets::Diff_Brown);
        int mine_size = MeasureText(TextFormat("%02i",CurrCell.mines), 35);
        DrawText(TextFormat("%02i",CurrCell.mines), 705 - (mine_size/2), 580 , 35, Assets::Diff_Brown); 
        
        
        
    }
}

#endif
