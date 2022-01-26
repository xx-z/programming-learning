/*****************************************************************************************************
*
*　main関数
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

//ゲームの数
#define MAXGAMENUMBER 2

//アルゴリズムゲームの数
#define MAXALGORITHMNUMBER 4

//指定の場所の画面リセット関数
void setCursorPos(int x, int y) {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}


void main() {
    int Scene = 0;
    int GameSlcNum = 0;                  //ゲームのセレクトナンバー
    int AlgoSlcNum = 0;                     //アルゴリズムゲームのセレクトナンバー

    int Flg = 1;
    //スタート画面 (start.c)
    StartDisplay();

    while (Flg == 1) {
        switch (Scene) {
        //ゲームセレクト画面
        case 0:
            printf("GameSelect\n\n");
            printf("　Algorithm Game\n　Sort Game");
            GameSlcNum = Select(MAXGAMENUMBER);
            if (GameSlcNum == 0) Scene = 1;
            else Scene = 2;
            break;
         //アルゴリズムゲーム
        case 1:
            printf("Algorithm Select\n\n");
            printf("　1\n　2\n　3\n　4\n");
            AlgoSlcNum = Select(MAXALGORITHMNUMBER);
            AlgorithmGame(AlgoSlcNum);
            Flg = 0;
            break;
         //ソート画面
        case 2:
            system("cls");
            printf("coming soon");
            Flg = 0;
            break;
        }
    }
}