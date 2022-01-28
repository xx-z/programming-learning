/*****************************************************************************************************
*
*　アルゴリズムゲーム
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
#include "algorithm.h"

//キー入力配列
int KeyList[MAXKEY] = { 0 };
//キー入力回数
int GetKeyCount = 0;

//マップの行列リスト
char MapList[MAXMAP][MAXMAP];
//マップのXYの最大サイズ
int MapSizeX = 0, MapSizeY = 0;

//現在のプレーヤーの座標
int PlayerPosX = 0, PlayerPosY = 0;

//ジャッチカウント
int JudgeCount = 0;


/// <summary>
/// 関数名 | AlgoMapLoad
/// 詳細　 | MapFile（マップファイル）のマップを読み込み
/// 　　　 | MapList（マップ行列）に代入
/// 　　　 | マップの最大サイズ計測（MapSizeX, Y）
/// </summary>
/// <param name="MapFile">マップファイルの名前</param>
void AlgoMapLoad(char MapFile[25]) {
    printf("%s", MapFile);
    const char* file = MapFile;
    FILE* fp;
    char c;
    int X = 0, Y = 0;

    //データの初期化
    JudgeCount = 0;
    for (int i = 0; i < MAXMAP; i++) {
        for (int j = 0; j < MAXMAP; j++) {
            MapList[i][j] = '4';
        }
    }

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("\nファイルエラー\n%sのオープンに失敗しました。\n", file);
        exit(1);
    }
    //EOFまでファイルから文字を1文字ずつ読み込む
    while ((c = fgetc(fp)) != EOF) {
        //読み込んだデータを二次元配列のMapListに代入
        if ('\n' == c) {
            if (MapSizeX < X) MapSizeX = X;
            Y++; X = 0;
        }
        else {
            if ('0' == c) JudgeCount++;     //クリア判定で使う0の個数を数える
            MapList[X][Y] = c; X++;
        }
    }
    MapSizeY = Y + 1;
    fclose(fp);
}


/// <summary>
/// 関数名 | AlgoMapDisplay
/// 詳細　 | MapList（マップ行列）の表示
/// 　　　 | 0 : 通っていない場所　1: 通った場所　2: プレーヤー　3: 壁
/// </summary>
void AlgoMapDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Algorithm Game\n\n");
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
            else if ('3' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("　");
            }
        }
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf("\n");
    }
    printf("\n□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n□□□□□□□□□□□□□□□□□□□□□□□□□□□□\n\n");
}


/// <summary>
/// 関数名 | AlgoKeyGet
/// 詳細　 | 入力キーをKeyListに代入
/// 　　　 | 矢印キー : 代入　バックスペース : 取り消し　エンター : 終了
/// </summary>
void AlgoKeyGet() {
    int Key = 0;                                         //キーの種類
    int Count = 0;                                      //入力回数
    GetKeyCount = 0;
    for (int i = 0; i < MAXKEY; i++) KeyList[i] = 0;

    //入力したキーをKeyListに代入
    while (GetKeyCount != MAXKEY) {
        switch (getch()) {

        //矢印キー
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

        //バックスペース
        case '\b':
            if (GetKeyCount != 0) {
                GetKeyCount--; Count--;
                KeyList[GetKeyCount] = 0;
                setCursorPos(Count * 2, MapSizeY + 4);
                printf("　");
                setCursorPos(Count * 2, MapSizeY + 4);
            }
            break;

        //エンター
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


/// <summary>
/// 関数名 | AlgoKeyDisplay
/// 詳細　 | KeyList（入力キー）の表示
/// 　　　 | 実行中の矢印キーの強調表示
/// </summary>
/// <param name="KeyNumber">キー入力配列の選択された値</param>
void AlgoKeyDisplay(KeyNumber) {
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


/// <summary>
/// 関数名 | AlgoExecution
/// 詳細　 | キー入力に応じてプレイヤーを移動させて表示させる
/// </summary>
void AlgoExecution() {
    for (int i = 0; i < GetKeyCount; i++) {
        //壁にぶつかっていない時、入力がない時
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
                if (MapList[PlayerPosX][PlayerPosY] == '0') JudgeCount--;
                MapList[PlayerPosX][PlayerPosY] = '2';
                setCursorPos(0, 0);
                AlgoMapDisplay();
            }
            //壁に当たった時
            else {
                setCursorPos(0, MapSizeY + INTERVAL);
            }
            AlgoKeyDisplay(i);
            Sleep(EXECUTIONSPEED);
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


/// <summary>
/// 関数名 | AlgoJudgement
/// 詳細　 | ClearCountが0の時にクリア
/// </summary>
void AlgoJudgement() {
    //入力キーの確認
    if (GetKeyCount != 0) {
        if (JudgeCount == 0) {
            TxtLoad(GAMECLEARTXT);
        }
        else {
            TxtLoad(GAMEFAILURE);
        }
        if (getchar() != '\n');
    }
}


/// <summary>
/// 関数名 | AlgorithmGame
/// 詳細　 | アルゴリズムゲームの全実行内容
/// </summary>
/// <param name="AlgoSlcNum">ステージの番号</param>
void AlgorithmGame(AlgoSlcNum) {
    //ステージ選択に合わせたマップの読み込み
    char MapFile[25];
    snprintf(MapFile, 25, "AlgoMap/map_%d.txt", AlgoSlcNum);
    AlgoMapLoad(MapFile);

    //マップ表示
    AlgoMapDisplay();

    //キーを入力
    AlgoKeyGet();
    
    //実行
    AlgoExecution();

    //結果判定
    AlgoJudgement();
}