/*****************************************************************************************************
*
*　アルゴリズムゲーム
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

#define  T_WHITE 0x0f
#define  T_RED 0x0c

#define MAXKEY 30                                       //最大キー入力回数
#define MAXMAP 20                                      //最大マップサイズ

int KeyList[MAXKEY] = { 0 };                          //キー入力配列
int GetKeyCount = 0;                                      //キー入力回数

char MapList[MAXMAP][MAXMAP];               //マップの行列リスト
int MapSizeX = 0, MapSizeY = 0;                   //マップのXYの最大サイズ

int PlayerPosX = 0, PlayerPosY = 0;              //現在のプレーヤーの座標

int ClearCount = 0;                                         //クリアカウント


/*****************************************************************************************************
* 関数名 | MapLoad
* 概要　 | マップの読み込み
* 引数　 | MapFile : マップファイルの名前
* 戻り値 | なし
* 詳細　 | マップファイルのマップを読み込み、MapList（マップ行列）に代入、マップの最大サイズ判定
*****************************************************************************************************/
void MapLoad(MapFile) {
    const char* file = MapFile;
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
        //二次元配列のMapListに代入
        if ('\n' == c) {
            if (MapSizeX < X) MapSizeX = X;
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


/*****************************************************************************************************
* 関数名 | MapDisplay
* 概要　 | マップの表示
* 引数　 | なし
* 戻り値 | なし
* 詳細　 | MapList（マップ行列）の表示
* 　　　 | 0 : 通っていない場所　1: 通った場所　2 : プレーヤー　3 : 壁
*****************************************************************************************************/
void MapDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n");
    //マップのサイズ分表示
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if ('0' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("□");
            }
            else if ('1' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_RED);
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


/*****************************************************************************************************
* 関数名 | KeyGet
* 概要　 | 入力キー
* 引数　 | なし
* 戻り値 | なし
* 詳細　 | 入力キーをKeyListに代入
*****************************************************************************************************/
void KeyGet() {
    int Key = 0;                                         //キーの種類
    int Count = 0;                                      //入力回数

    //入力したキーをKeyListに代入
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
    //入力回数を代入
    GetKeyCount = Count;
    printf("\n");
}


/*****************************************************************************************************
* 関数名 | KeyDisplay
* 概要　 | 入力キーの表示、強調表示
* 引数　 | KeyNumber（キー入力配列の選択された値）
* 戻り値 | なし
* 詳細　 | KeyList（入力キー）の表示、実行中の矢印キーの強調表示
*****************************************************************************************************/
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


/*****************************************************************************************************
* 関数名 | Execution
* 概要　 | 入力キーを実行
* 引数　 | なし
* 戻り値 | なし
* 詳細　 | キー入力に応じてプレイヤーを移動させて表示させる
*****************************************************************************************************/
void Execution() {
    for (int i = 0; i < GetKeyCount; i++) {
        while (MapList[PlayerPosX][PlayerPosY] != '3') {
            //入力キーに合わせて１つ移動
            switch (KeyList[i]) {
            case 1: PlayerPosY--; break;
            case 2: PlayerPosX++; break;
            case 3: PlayerPosY++; break;
            case 4: PlayerPosX--; break;
            }
            //壁に当たっていないとき
            if (MapList[PlayerPosX][PlayerPosY] != '3') {
                if (MapList[PlayerPosX][PlayerPosY] == '0') ClearCount--;
                MapList[PlayerPosX][PlayerPosY] = '2';
                setCursorPos(0, 0);
                MapDisplay();
            }
            //壁に当たった時
            else {
                setCursorPos(0, MapSizeY + 4);
            }
            KeyDisplay(i);
            Sleep(700);
        }
        //壁にぶつかっているので戻る
        switch (KeyList[i]) {
        case 1: PlayerPosY++; break;
        case 2: PlayerPosX--; break;
        case 3: PlayerPosY--; break;
        case 4: PlayerPosX++; break;
        }
    }
}


/*****************************************************************************************************
* 関数名 | Judgement
* 概要　 | クリア判定
* 引数　 | なし
* 戻り値 | なし
* 詳細　 | ClearCountが0の時にクリア
*****************************************************************************************************/
void Judgement() {
    if (ClearCount == 0) printf("\n\nGame Clear!");
    else printf("\n\nFailure");
}


/*****************************************************************************************************
* 関数名 | AlgorithmGame
* 概要　 | アルゴリズムゲームのmain関数
* 引数　 | AlgoSlcNum（ステージの番号）
* 戻り値 | なし
* 詳細　 | アルゴリズムゲームの全実行内容
*****************************************************************************************************/
void AlgorithmGame(AlgoSlcNum) {
    //ステージ選択に合わせたマップの読み込み
    char MapFile[10];
    snprintf(MapFile, 10, "map_%d.txt", AlgoSlcNum);
    MapLoad(MapFile);

    //マップ表示
    MapDisplay();

    //キーを入力
    KeyGet();

    //実行
    Execution();

    //結果判定
    Judgement();
}