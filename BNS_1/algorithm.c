#include <stdio.h>
#include <conio.h>
#include <Windows.h>

#include "ColorData.h"

//最大キー入力回数
#define MAXKEY 30
//最大マップサイズ
#define MAXMAP 20

//キー入力リスト
int KeyList[MAXKEY] = { 0 };
//キー入力回数
int GetKeyCount = 0;

//マップの行列リスト
char MapList[MAXMAP][MAXMAP];
//マップのXYの最大サイズ
int MapSizeX = 0, MapSizeY = 0;

//現在のプレーヤーの座標
int PlayerPosX = 0, PlayerPosY = 0;

//クリアカウント
int ClearCount = 0;


//マップの読み込み
void MapLoad() {
    const char* file = "map_1.txt";
    FILE* fp;
    char c;
    int X = 0, Y = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("ファイルエラー\n%sのオープンに失敗しました。\n", file);
        exit(1);
    }
    //EOFまでファイルから文字を1文字ずつ読み込む
    while ((c = fgetc(fp)) != EOF) {
        if ('\n' == c) {
            if (MapSizeX < X) {
                MapSizeX = X;
            }
            Y++; X = 0;
        }
        else {
            if ('0' == c) ClearCount++;
            MapList[X][Y] = c; X++;
        }
    }
    MapSizeY = Y + 1;
    fclose(fp);
}

//マップの表示
void MapDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n");
    //0:off   1:on   2:start   3:wall
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if ('0' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("□");
            }
            else if ('1' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_DARK_RED);
                printf("■");
            }
            else if ('2' == MapList[j][i]) {
                PlayerPosX = j; PlayerPosY = i;
                MapList[j][i] = '1';
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("　");
            }
            else {
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("　");
            }
        }
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf("\n");
    }
    printf("\n＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n\n");
}

//キー入力検知
void KeyGet() {
    int Key = 0;
    int Count = 0;

    while (GetKeyCount != MAXKEY) {
        switch (getch()) {
        case 0xe0:
            switch (getch()) {
            case 0x48: Key = 1; printf("↑"); break;
            case 0x4d: Key = 2; printf("→"); break;
            case 0x50: Key = 3; printf("↓"); break;
            case 0x4b: Key = 4; printf("←"); break;
            }
            KeyList[GetKeyCount] = Key;
            GetKeyCount++; Count++;
            break;
        case 0x0d:
            Count = GetKeyCount;
            GetKeyCount = MAXKEY;
            break;
        }
    }
    GetKeyCount = Count;
    printf("\n");
}

void setCursorPos(int x, int y) {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}

void KeyDisplay(KeyNumber) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < GetKeyCount; i++) {
        if (KeyNumber == i) {
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
        }
        else {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        }
        switch (KeyList[i]) {
        case 1: printf("↑"); break;
        case 2: printf("→"); break;
        case 3: printf("↓"); break;
        case 4: printf("←"); break;
        }
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
}

void ExecutionDisplay() {
    setCursorPos(0, 0);
    MapDisplay();
}

void Execution() {
    //printf("%d%d", PlayerPosX, PlayerPosY);
    for (int i = 0; i < GetKeyCount; i++) {
        while (MapList[PlayerPosX][PlayerPosY] != '3') {
            switch (KeyList[i]) {
            case 1: PlayerPosY--; break;
            case 2: PlayerPosX++; break;
            case 3: PlayerPosY++; break;
            case 4: PlayerPosX--; break;
            }
            if (MapList[PlayerPosX][PlayerPosY] != '3') {
                if (MapList[PlayerPosX][PlayerPosY] == '0') ClearCount--;
                MapList[PlayerPosX][PlayerPosY] = '2';
                ExecutionDisplay();
                KeyDisplay(i);
            }
            else {
                setCursorPos(0, MapSizeY + 4);
                KeyDisplay(i);
            }
            Sleep(1000);
        }
        if (MapList[PlayerPosX][PlayerPosY] == '3') {
            switch (KeyList[i]) {
            case 1: PlayerPosY++; break;
            case 2: PlayerPosX--; break;
            case 3: PlayerPosY--; break;
            case 4: PlayerPosX++; break;
            }
        }
    }
}

void Clear() {
    if (ClearCount == 0) printf("\n\nGame Clear!");
    else printf("\n\nFailure");
}

void main() {
    MapLoad();
    MapDisplay();
    KeyGet();
    Execution();
    Clear();
}