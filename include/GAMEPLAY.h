#ifndef GAMEPLAY_h
#define GAMEPLAY_h

#include "raylib.h"
#include "raymath.h"

#include "PROPERTIES.h"
#include "FUNCTION.h"

namespace Gemu
{
    static Texture2D GP_background, GP_pausebutton, GP_bomb, GP_flag;
    struct msh { int x; int y;} mouseHooverCell = {-1,-1};
    bool mouseHooverPause = 0;
    
    void LoadAllTexture()
    {
        GP_background = LoadTexture("./resource/GP_bg.png");
        GP_pausebutton = LoadTexture("./resource/GP_pausebutton.png");
        GP_bomb = LoadTexture("./resource/GP_bomb.png");
        GP_flag = LoadTexture("./resource/GP_flag.png");
    }

void UnLoadAllTexture()
{
    UnloadTexture(GP_background);
    UnloadTexture(GP_pausebutton);
    UnloadTexture(GP_bomb);
    UnloadTexture(GP_flag);
}

    void PausePress()
    {
        is_count_Time = false;
        currentScreen = pausemenu;
    }

    void Win()
    {
        GameStatus = true; is_count_Time = false; is_count_frame = true;
        if (AreSame(BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}],0) == false)
        {
            BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}] = std::min(Timer,BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}]);
        }
        else BestScore[{CurrCell.rows, CurrCell.cols, CurrCell.mines}] = Timer;
    }

void GameOver()
{

    GameStatus = false; is_count_Time = false; is_count_frame = true;
}

    void pressleftbutton(int i, int j)
    {
        if (!is_count_frame)
        {
            if (x_click == 0)
            {
                x_click = i; y_click = j;
                gen_mines();
                if (number[x_click][y_click] == 0) BFS(i, j);
                else { is_Open[x_click][y_click] = true; ++cntopen;}
                is_count_Time = true;
            }
            else
            {
                if (is_Flaged[i][j] == 0)
                {
                    if (is_Bomb[i][j]) 
                    {
                        GameOver();
                    }
                    else
                    {
                        if (number[i][j] == 0) BFS(i,j);
                        else { is_Open[i][j] = true; ++cntopen;}
                    }
                }
            }
        }
    }

    bool checksurround(int i, int j)
    {
        int countflag = 0, countbomb = 0;
        for (int k = 0; k < 8; ++k)
        {
            if (CheckValid(i+dx[k], j+dy[k]))
            {
                if (is_Bomb[i+dx[k]][j+dy[k]]) ++countbomb;
                if (is_Flaged[i+dx[k]][j+dy[k]]) ++countflag;
            }
        }
        if (countbomb == countflag) //check
        {
            for (int k = 0; k < 8; ++k)
            {
                if (is_Bomb[i+dx[k]][j+dy[k]])
                {
                    if (!is_Flaged[i+dx[k]][j+dy[k]]) return false;
                }
            }
        }
        else return false;
        return true;
    }


    void pressrightbutton(int i, int j)
    {
        if (is_Open[i][j] == false)
        {
            if (is_Flaged[i][j]) ++cntflag;
            else --cntflag;
            is_Flaged[i][j] = !is_Flaged[i][j];
                
        }
        else
        {
            bool checkwl = checksurround(i, j);
            if (!checkwl) GameOver();
            else
            {
                for (int k = 0; k < 8 ; ++k)
                {
                    if (CheckValid(i+dx[k], j+dy[k]))
                    {
                        if ((is_Open[i+dx[k]][j+dy[k]] == false) && (is_Bomb[i+dx[k]][j+dy[k]] == false))
                            {
                            if (number[i+dx[k]][j+dy[k]] == 0) BFS(i+dx[k],j+dy[k]);
                            else is_Open[i+dx[k]][j+dy[k]] = true;
                        }
                    }
                }
            }
        }
    }

    void DrawButton(int i, int j)
    {
            if (!is_Open[i][j])
            {
                if ((i%2!=0 && j%2!=0) || (i%2==0 && j%2==0)) DrawRectangleRec(posCell[i][j], Fade(Assets::HardRed,(mouseHooverCell.x == i && mouseHooverCell.y == j) ? 0.7f : 1.0f));
                else DrawRectangleRec(posCell[i][j], Fade(Assets::LightRed,(mouseHooverCell.x == i && mouseHooverCell.y == j) ? 0.7f : 1.0f));
                if (is_Flaged[i][j]) DrawTexturePro(GP_flag, (Rectangle){0,0,850,850}, posCell[i][j], {0.0,0.0}, 0, WHITE);
            }
            else 
            {
                if ((i%2!=0 && j%2!=0) || (i%2==0 && j%2==0)) DrawRectangleRec(posCell[i][j], Assets::HardBrown);
                else DrawRectangleRec(posCell[i][j], Assets::LightBrown);
                if (number[i][j]!=0)
                {
                    int num_size = MeasureText(TextFormat("%01i",number[i][j]), posCell[i][j].width - 10);
                    DrawText(TextFormat("%01i",number[i][j]), posCell[i][j].x + (posCell[i][j].width/2) - (num_size/2), posCell[i][j].y + (posCell[i][j].height/2) - (posCell[i][j].width - 10)/2, posCell[i][j].width - 10 , Assets::Diff_Brown);
                }
            }
            if (is_count_frame && is_Bomb[i][j])
                DrawTexturePro(GP_bomb, (Rectangle){0,0,850,850}, posCell[i][j], {0.0,0.0}, 0, WHITE);
    }

    void BuildGameScreen() //w: 1130, h: 620
    {
        StartStatus();
        DrawTexture(GP_background, 0, 0, WHITE);
        
        if (countcnt() == ((CurrCell.cols * CurrCell.rows) - CurrCell.mines)) Win();
        
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            bool checki = false;
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                if (CheckCollisionPointRec(GetMousePosition(), posCell[i][j]))
                {
                    mouseHooverCell = {i,j};
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) pressleftbutton(i, j);
                    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) pressrightbutton(i, j);
                    checki = true;
                    break;
                }
                else mouseHooverCell = {-1,-1};
            }
            if (checki) break;
        }
        
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
                DrawButton(i, j);
        }
        
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){591, 40, 97, 96}))
        {
            mouseHooverPause = true;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) PausePress();
        }
        else mouseHooverPause = false;
        
        DrawTexture(GP_pausebutton, 591, 40, (mouseHooverPause == false) ? WHITE : GRAY);
        
        DrawText(TextFormat("Time: %03.02f", Timer), 270, 72, 35, GRAY);
        DrawText(TextFormat("Flag: %02i", cntflag), 850, 72, 35, GRAY);
        
    }
}

#endif
