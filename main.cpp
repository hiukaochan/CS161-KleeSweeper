#include <iostream>
#include <unistd.h>

#include "raylib.h"
#include "raymath.h"

/*#ifndef __APPLE__
    #define MA_NO_RUNTIME_LINKING
#endif

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"*/

#include "PROPERTIES.h"
#include "MAINMENU.h"
#include "DIFFICULTY.h"
#include "GAMEPLAY.h"
#include "WINLOSE.h"
#include "PAUSEMENU.h"

const int screenWidth = 1280;
const int screenHeight = 850;

//using namespace raylib;

int main()
{

    // Initialization()
    InitWindow(screenWidth, screenHeight, "KleeSweeper - Cao Thanh Hieu");
    InitAudioDevice();
    
    //Game loop
    //chdir("./");
    
    ReadHighScore();
    
    SetTargetFPS(60);
    
    Assets::LoadallTexture();
    
    diff::LoadallTexture();
    
    pause_ns::LoadallTexture();
    
    wlscreen::LoadallTexture();
    
    Gemu::LoadAllTexture();
    
    currentScreen = mainmenu;
    
    while (!WindowShouldClose())
    {
        
        SaveFileValid = IsSavedFileValid();
        
        //SaveHighscore();
        
        BeginDrawing();
        
        switch (currentScreen) {
            case mainmenu:
            {
                Menu::DrawMenu();
                break;
            }
            case difficulty:
            {
                diff::DrawDiff();
                break;
            }
            case gameplay:
            {
                TimeCount();
                Wait3sec();
                Gemu::BuildGameScreen();
                break;
            }
            case winlose:
            {
                wlscreen::DrawScreen();
                break;
            }
            case savedgame:
            {
                ReadSavedGame();
                if (!is_count_Time) is_count_Time = true;
                currentScreen = gameplay;
                break;
            }
            case pausemenu:
            {
                pause_ns::DrawallTexture();
                break;
            }
            default:
                break;
        }
        
        //loadBg_Music();
        
        EndDrawing();
    }
    
    // Shut Down
    
    SaveHighscore();
    
    
    diff::diff_UnloadTexture();
    
    Menu::UnLoadMenuTexture();
    
    wlscreen::UnloadallTexture();
    
    Gemu::UnLoadAllTexture();
    
    pause_ns::UnLoadallTexture();
    
    CloseWindow();
    CloseAudioDevice();
}
