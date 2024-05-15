#ifndef PAUSEMENU_h
#define PAUSEMENU_h

#include "WINLOSE.h"

namespace pause_ns
{
    static Texture2D Pau_resume, Pau_save, Pau_quit, Pau_BG, Pau_reset;
    int mouseHooverpause = -1;
    Rectangle pausebutton[4] ={{417,280,447,65},{417,380,447,65},{417,480,447,65},{417,580,447,65}};

    void LoadallTexture()
    {
        Pau_resume = LoadTexture("./resource/Pau_resume.png");
        Pau_save = LoadTexture("./resource/Pau_save.png");
        Pau_quit = LoadTexture("./resource/Pau_quit.png");
        Pau_BG = LoadTexture("./resource/Pau_BG.png");
        Pau_reset = LoadTexture("./resource/Pau_reset.png");
    }

void UnLoadallTexture()
{
    UnloadTexture(Pau_resume);
    UnloadTexture(Pau_save);
    UnloadTexture(Pau_quit);
    UnloadTexture(Pau_BG);
    UnloadTexture(Pau_reset);
}

    void Resume()
    {
        if (!is_count_Time) is_count_Time = true;
        currentScreen = gameplay;
    }

    void SaveAction()
    {
        is_count_Time = false;
        saveout.open(savedfile);
        if (saveout.is_open())
        {
            saveout << 1 << '\n';
            saveout << x_click << " " << y_click << " " << CurrCell.rows << " " << CurrCell.cols << " " << CurrCell.mines << " " << Timer << " " << cntflag << '\n';
            for (int i = 1; i <= CurrCell.rows; ++i)
            {
                for (int j = 1; j <= CurrCell.cols; ++j)
                {
                    saveout << number[i][j] << " ";
                }
                saveout << '\n';
            }
            
            for (int i = 1; i <= CurrCell.rows; ++i)
            {
                for (int j = 1; j <= CurrCell.cols; ++j)
                {
                    saveout << is_Bomb[i][j] << " ";
                }
                saveout << '\n';
            }
            
            for (int i = 1; i <= CurrCell.rows; ++i)
            {
                for (int j = 1; j <= CurrCell.cols; ++j)
                {
                    saveout << is_Flaged[i][j] << " ";
                }
                saveout << '\n';
            }
            for (int i = 1; i <= CurrCell.rows; ++i)
            {
                for (int j = 1; j <= CurrCell.cols; ++j)
                {
                    saveout << is_Open[i][j] << " ";
                }
                saveout << '\n';
            }
        }
        saveout.close();
        currentScreen = mainmenu;
    }

    void DrawallTexture()
    {
        
        for (int i = 0; i < 4; ++i)
        {
            if (CheckCollisionPointRec(GetMousePosition(), pausebutton[i]))
            {
                mouseHooverpause = i;
                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
                {
                    switch (i)
                    {
                        case 1:
                        {
                            Resume();
                            break;
                        }
                        case 2:
                        {
                            SaveAction();
                            break;
                        }
                        case 3:
                        {
                            wlscreen::MainMenuPress();
                            break;
                        }
                        case 0:
                        {
                            wlscreen::PlayAgainPress();
                            break;
                        }
                        default:
                            break;
                    }
                }
                break; // important!
            }
            else mouseHooverpause = -1;
        }
            DrawTexture(Pau_BG, 0, 0, WHITE);
            DrawTexture(Pau_reset, 417, 280, (mouseHooverpause == 0) ? GRAY: WHITE);
            DrawTexture(Pau_resume, 417, 380, (mouseHooverpause == 1) ? GRAY: WHITE);
            DrawTexture(Pau_save, 417, 480, (mouseHooverpause == 2) ? GRAY: WHITE);
            DrawTexture(Pau_quit, 417, 580, (mouseHooverpause == 3) ? GRAY: WHITE);
    }
}


#endif
