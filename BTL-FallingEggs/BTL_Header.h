#ifndef BTL_HEADER_H_INCLUDED
#define BTL_HEADER_H_INCLUDED

#include<iostream>
#include<conio.h>
#include<dos.h>
#include<windows.h>
#include<time.h>
#include<fstream>
#include<cstdio>
#include<vector>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;


void gotoxy(int x, int y);
void setcursor(bool visible, DWORD size);
void drawBorder();
void genTarget(int ind);
void drawTarget(int ind);
void eraseTarget(int ind);
void resetTarget(int ind);
void drawBasket();
void eraseBasket();
void gameover();
void updateScore();
void instructions();
void gameStatus();
void startGame();
void play(int hard);
bool collision();
void startMenu();
void chonDoKho();
void updateHp();
void clearHp();
void updateHighScore();
void leaderboard();
void getName();
void updateName();
void outputScore();
void leaderboard();
void outputName();
void loadingAnimation();
void copyright();

#endif // BTL_HEADER_H_INCLUDED
