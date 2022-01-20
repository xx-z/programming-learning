#include <stdio.h>
#include <Windows.h>

#define MAXKEY 30                                      //最大キー入力回数
#define MAXMAP 20                                   //最大マップサイズ

int KeyList[MAXKEY] = { 0 };                        //キー入力リスト
int GetKeyCount = 0;                                    //キー入力回数

char MapList[MAXMAP][MAXMAP];              //マップの行列リスト
int MapSizeX, MapSizeY = 0;                         //マップのXYの最大サイズ

int PlayerPosX, PlayerPosY = 0;                     //現在のプレーヤーの座標

//マップの読み込み
void MapLoad() {
    const char* file = "map_1.txt";
    FILE* fp;
    char c;
    int X = 0;
    int Y = 0;                                                   

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
            MapList[X][Y] = c; X++;
        }
    }
    MapSizeY = Y + 1;
    fclose(fp);
}

//マップの表示
void MapDisplay() {
    printf("\n");
    //本マップ生成
    //0:off   1:on   2:start   3:wall
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if ('0' == MapList[j][i]) {
                printf("□");
            } else if ('1' == MapList[j][i]) {
                printf("\x1b[31m■\x1b[m");
            } else if ('2' == MapList[j][i]){
                PlayerPosX = j; PlayerPosY = i;
                MapList[j][i] = '1';
                printf("\x1b[44m　\x1b[m");
            } else {
                printf("\x1b[47m　\x1b[m");
            }
        }
        printf("\n");
    }
}

//キーリストにキーを代入する関数
void KeyAdd(Key) {
    KeyList[GetKeyCount] = Key;
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
            KeyAdd(Key);
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
    //printf("%d\n", GetKeyCount);
}

void setCursorPos(int x, int y)
{
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}

void ExecutionDisplay() {
    setCursorPos(0, 0);
    MapDisplay();
    Sleep(1000);
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
                MapList[PlayerPosX][PlayerPosY] = '2';
                ExecutionDisplay();
            }
        } 
        if (MapList[PlayerPosX][PlayerPosY] == '3') {
            switch (KeyList[i]) {
                case 1: PlayerPosY++; break;
                case 2: PlayerPosX--; break;
                case 3: PlayerPosY--; break;
                case 4: PlayerPosX++; break;
            }
        }
        //printf(", %d%d", PlayerPosX, PlayerPosY);
    }
}



void main() {
    MapLoad();
    MapDisplay();
    printf("\n＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊＊\n\n");
    KeyGet();
    Execution();
}

/*
printf("\x1b[41m　\x1b[m\n"); 
printf("\x1b[34m□□□□■■■■\033[m\n");
*/