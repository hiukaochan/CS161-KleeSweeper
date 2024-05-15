#ifndef FUNCTION_h
#define FUNCTION_h

#include "PROPERTIES.h"

#include <time.h>
#include <random>
#include <chrono>
#include <ctime>
#include <queue>
#include <vector>

std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

std::vector<bool>randombombs;

int RandInt(int l, int r)
{
    return l + rng()%(r-l+1);
}

bool CheckValid(int x, int y)
{
    return (x>=1 && x<=CurrCell.rows && y>=1 && y<=CurrCell.cols);
}

bool Check_no_bomb_near(int x, int y, int x1, int y1) // cant work with 3x3
{
    for (int i=0;i<8;++i)
        if (x+dx[i]==x1 && y+dy[i]==y1) return false;
    return true;
}

int gen_num(int x, int y)
{
    int temp_num = 0;
    for (int i=0;i<8;++i)
            if (CheckValid(x+dx[i],y+dy[i]) && is_Bomb[x+dx[i]][y+dy[i]]) ++temp_num;
    return temp_num;
}

void gen_mines()
{
    int bomb=CurrCell.mines, surroundfirstclick = 0;
    bool temp = false;
    
    for (int i = 0 ; i < 8 ; ++i)
    {
        if (CheckValid(x_click + dx[i], y_click + dy[i])) ++surroundfirstclick;
    }
    
    if (CurrCell.rows * CurrCell.cols - surroundfirstclick - 1 >= CurrCell.mines)  temp = false;
    else temp = true;
    
    randombombs.resize(CurrCell.rows*CurrCell.cols + 1);
    
    for (int i = 1; i <= CurrCell.rows*CurrCell.cols +1; ++i)
    {
        if (i <= bomb) randombombs[i] = 1;
        else randombombs[i] = 0;
    }
    
    shuffle(randombombs.begin() + 1, randombombs.end(), rng);
    
    int k = 1;
    
    for (int i = 1; i <= CurrCell.rows; ++i)
    {
        for (int j = 1; j <= CurrCell.cols; ++j)
        {
            if (randombombs[k]) is_Bomb[i][j] = true;
            ++k;
        }
    }
    
    // no bomb first click
    
    if (!temp) //temp>=CurrCell.mines
    {
        //check no bombs on first click
        if (is_Bomb[x_click][y_click])
        {
            bool check = false;
            while (!check)
            {
                int temp_rows = RandInt(1, CurrCell.rows);
                for (int j = 1; j <= CurrCell.cols; ++j)
                {
                    if (is_Bomb[temp_rows][j] == false && Check_no_bomb_near(x_click, y_click, temp_rows, j) && !(x_click == temp_rows && y_click == j))
                    {
                        is_Bomb[temp_rows][j] = true;
                        is_Bomb[x_click][y_click] = false;
                        check = true;
                        break;
                    }
                }
            }
        }
        
        //check no bomb near first click
        for (int i = 0 ; i < 8; ++i)
        {
            if (is_Bomb[x_click + dx[i]][y_click + dy[i]])
            {
                bool check = false;
                while (!check)
                {
                    int temp_rows = RandInt(1, CurrCell.rows);
                    for (int j = 1; j <= CurrCell.cols; ++j)
                    {
                        if (is_Bomb[temp_rows][j] == false && Check_no_bomb_near(x_click, y_click, temp_rows, j) && !(x_click == temp_rows && y_click == j))
                        {
                            is_Bomb[temp_rows][j] = true;
                            is_Bomb[x_click + dx[i]][y_click + dy[i]] = false;
                            check = true;
                            break;
                        }
                    }
                }
            }
        }
    }
    else
    {
        // check first click
        bool check1 = true;
        if (is_Bomb[x_click][y_click])
        {
            for (int i = 1; i <= CurrCell.rows; ++i)
            {
                for (int j = 1; j <= CurrCell.cols; ++j)
                    if (is_Bomb[i][j] == false && !(x_click == i && y_click == j))
                    {
                        is_Bomb[i][j] = true;
                        is_Bomb[x_click][y_click] = false;
                        check1=false; break;
                    }
                if (!check1) break;
            }
        }
        
        int temp1 = 0;
        for (int i = 1; i <= CurrCell.rows; ++i)
        {
            for (int j = 1; j <= CurrCell.cols; ++j)
            {
                if (is_Bomb[i][j] == false && Check_no_bomb_near(x_click, y_click, i, j) && !(x_click == i && y_click == j))
                { is_Bomb[i][j] = true; ++temp1; }
            }
        }
        for (int i = 0; i < 8; ++i)
        {
            if (is_Bomb[x_click + dx[i]][y_click + dy[i]] && temp1 != 0)
            {
                is_Bomb[x_click + dx[i]][y_click + dy[i]] = false;
                --temp1;
            }
        }
    }
    for (int i = 1; i <= CurrCell.rows; ++i)
    {
        for (int j = 1; j <= CurrCell.cols; ++j)
            if (!is_Bomb[i][j]) number[i][j] = gen_num(i,j);
    }
    
}

void BFS(int x, int y)
{
    std::queue<std::pair<int,int>> Q;
    Q.push({x,y});
    is_Open[x][y]=true;
    ++cntopen;
    while (!Q.empty())
    {
        int r=Q.front().first, c=Q.front().second;
        Q.pop();
        for (int i=0;i<8;++i)
        {
            int x1=r+dx[i],y1=c+dy[i];
            int v=number[x1][y1];
            if (CheckValid(x1,y1) && !is_Open[x1][y1])
            {
                if (v==0) Q.push(std::make_pair(x1,y1));
                is_Open[x1][y1]=true;
                ++cntopen;
            }
        }
    }
}

int countcnt()
{
    int cnt = 0;
    for (int i = 1; i <= CurrCell.rows ; ++i)
    {
        for (int j = 1; j <= CurrCell.cols; ++j)
        {
            if (is_Open[i][j]) ++cnt;
        }
    }
    return cnt;
}


void StartStatus()
{
    int sizecells = std::min(1130/CurrCell.cols, 620/CurrCell.rows);
    int start_x = 640 - (sizecells*CurrCell.cols/2), start_y = 460 - (sizecells * CurrCell.rows/2);
    
    for (int i = 1; i <= CurrCell.rows ; ++i)
    {
        for (int j = 1; j <= CurrCell.cols; ++j)
        {
            int posx = start_x + (sizecells*(j-1)), posy = start_y + (sizecells*(i-1));
            posCell[i][j] = {(float)posx,(float)posy,(float)sizecells,(float)sizecells};
        }
    }
}

#endif
