#ifndef PROPERTIES_h
#define PROPERTIES_h

#include <iostream>
#include <fstream>
#include <cmath>
#include <map>
#include "raylib.h"

const int MIN_ROW = 3;
const int MIN_COL = 3;
const int MIN_MINE = 1;

const int MAX_ROW = 16;
const int MAX_COL = 30;

bool pause_Music = 0, CheckWindowClose = false, saveGameload = false;

int defaultrow[3]={9,16,16}, defaultcol[3]={9,16,30}, defaultmine[3]={10,40,99};
int cntflag = 0;

//home-made Timer
float Timer = 0.0;
bool is_count_Time = false;

void TimeCount()
{
    if (is_count_Time)
    {
        Timer += 0.016;
    }
}

Rectangle posCell[17][31];

struct CurrGame
{
    int rows, cols, mines;
};

CurrGame CurrCell = {10,10,30};

typedef enum GameScreen
{
    mainmenu = 0,
    difficulty,
    savedgame,
    gameplay,
    pausemenu,
    winlose
    
} GameScreen;

GameScreen currentScreen;

int dx[8] = {-1,-1,-1,0,1,1,1,0}, dy[8] = {-1,0,1,1,1,0,-1,-1}, number[17][31], x_click = 0, y_click = 0, cntopen = 0;
bool is_Bomb[17][31], is_Open[17][31], is_Flaged[17][31], GameStatus = true;

float hightime[17][31][481];

int FrameCount = 0;
bool is_count_frame = false;

void Wait3sec()
{
    if (is_count_frame)
    {
        ++FrameCount;
        if (FrameCount / 60.0 == 1.5) { FrameCount = 0; is_count_frame = false; currentScreen = winlose; }
    }
}

namespace Assets 
{
    Color DarkPurple, Diff_Brown, HardRed, LightRed, HardBrown, LightBrown,RedText;
    Rectangle MusicIcon;

    void LoadallTexture()
    {
        DarkPurple = GetColor(0x2c2732ff);
        Diff_Brown = GetColor(0x725647ff);
        HardRed = GetColor(0xDA696Bff);
        HardBrown = GetColor(0xF9E5CAff);
        LightRed = GetColor(0xE77074ff);
        LightBrown = GetColor(0xFFF4E5ff);
        RedText = GetColor(0xD14D52ff);
        MusicIcon = {50,50,75,75};
        
    }

}

void loadMusic_icon(Texture2D a)
{
    DrawTexture(a, 50, 30, WHITE);
}
//saved game

bool SaveFileValid = false;
std::ifstream savein;
std::ofstream saveout;
const char* savedfile = "./build/savegame.txt";

bool IsSavedFileValid()
{
    int temp = 0; bool ans = false;
    savein.open(savedfile);
    if (savein.is_open())
    {
        savein >> temp;
        if (temp == 1) ans = true;
    }
    savein.close();
    return ans;
}

void ReadSavedGame()
{
    saveGameload = true;
    savein.open(savedfile);
    if (savein.is_open())
    {
        int temp; savein >> temp;
        savein >>x_click >> y_click>> CurrCell.rows >> CurrCell.cols >> CurrCell.mines >> Timer >> cntflag;
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                savein >> number[i][j];
            }
        }
        
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                savein >> is_Bomb[i][j];
            }
        }
        
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                savein >> is_Flaged[i][j];
            }
        }
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                savein >> is_Open[i][j];
            }
        }
    }
    savein.close();
    
    saveout.open(savedfile);
    if (saveout.is_open())
    {
        saveout << 0;
    }
    saveout.close();
}

//highscore

std::map<std::tuple<int, int, int>, float > BestScore;
std::ifstream hsin;
std::ofstream hsout;
const char* scorefile = "./build/highscore.txt";

void ReadHighScore()
{
    hsin.open(scorefile);
    if (hsin.is_open())
    {
        int r,c,b; float t;
        while (hsin >> r >> c >> b >> t)
        {
            if ((MIN_ROW <= r && r <= MAX_ROW && MIN_COL <= c && c <= MAX_COL && MIN_MINE <= b && b <= r * c - 1))
                BestScore[std::make_tuple(r, c, b)] = t;
        }
    }
}

bool AreSame(float a, float b)
{
    return fabs(a - b) < EPSILON;
}

void SaveHighscore()
{
    hsout.open(scorefile);
    if (hsout.is_open())
    {
        bool firstLine = true;
        for (auto e : BestScore)
        {
            std::tuple<int, int, int> eFirst; float score;
            std::tie(eFirst, score) = e;
            int rows, cols, bombs; std::tie(rows, cols, bombs) = eFirst;
            if (AreSame(score, 0.0) == false)
            {
                if (!firstLine) hsout << std::endl;
                firstLine = false;
                hsout << rows << " " << cols << " " << bombs << " " << score;
            }
        }
    }
}

#endif
