/*****************************************************************************************************
*
*   ソートゲーム
*   
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
#include "sort.h"

//入力キーのリスト
int SortKeyList[MAXKEY] = { 0 };
//ソートのマップリスト
int SortMapList[MAXMAP] = { 0 };

//キーの入力回数
int SortGetKeyCount = 0;
//ソートマップのサイズ
int SortMapCount = 0;


/// <summary>
/// 関数名 | SortMapLoad
/// 詳細　 | 行数（ステージ）に合わせたマップの読み込み
/// </summary>
/// <param name="Line">読み込む行数</param>
void SortMapLoad(int Line) {
    const char* file = "data/sort_map.txt";
    FILE* fp;
    char c;
    //行数の回数
    int LineCount = 0;
    //ソートマップのサイズをリセット
    SortMapCount = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("\nファイルエラー\n%sのオープンに失敗しました。\n", file);
        exit(1);
    }
    //EOFまでファイルから文字を1文字ずつ読み込む
    while ((c = fgetc(fp)) != EOF) {
        if ('\n' == c) LineCount++;
        if (Line == LineCount && '\n' != c) {
            SortMapList[SortMapCount] = c;
            SortMapCount++;
        }
    }
    fclose(fp);
}

/// <summary>
/// 関数名 | SortHeadDisplay
/// 詳細　 | 答えとなる列の表示
/// 　　　 | 数字はブロックとなるように色付けする
/// </summary>
void SortHeadDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < SortMapCount; i++) {
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf(" ");
        SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
        printf(" %d ", i);
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
    printf(" ");
}


/// <summary>
/// 関数名 | SortMapDisplay
/// 詳細　 | ソートマップの表示
/// 　　　 | 入力キーに合わせて色付けする
/// </summary>
/// <param name="Key">ソートマップの表示</param>
void SortMapDisplay(int Key) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    setCursorPos(1, 1);
    for (int i = 0; i < SortMapCount; i++) {
        if (Key == i) {
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_RED | BACKGROUND_INTENSITY | T_WHITE);
        }
        else {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        }
        printf(" %c ", SortMapList[i]);
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf(" ");
    }
    printf("\n\n");
}


/// <summary>
/// 関数名 | SortKeyDisplay
/// 詳細　 | 選択したキーを表示する
/// </summary>
void SortKeyDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < SortGetKeyCount; i++) {
        if (i % 2 == 0) {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(" (");
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
            printf(" %d ", SortKeyList[i]);
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(" ⇔");
        }
        else {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(" ");
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
            printf(" %d ", SortKeyList[i]);
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(") →");
        }
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
}


/// <summary>
/// 関数名 | SortKeyGet
/// 詳細　 | キー入力をキーリスト（SortKeyList[]）に代入する
/// </summary>
void SortKeyGet() {
    int Key = 0;                                         //キーの種類
    int Count = 0;                                      //入力回数
    //初期化
    SortGetKeyCount = 0;
    for (int i = 0; i < MAXKEY; i++) SortKeyList[i] = 0;

    //入力したキーをKeyListに代入
    while (SortGetKeyCount != MAXKEY) {
        //マップとキーを表示
        SortMapDisplay(Key);
        SortKeyDisplay();

        switch (getch()) {
        //矢印キー
        case 0xe0:
            switch (getch()) {
            case 0x4d:  //→
                Key++;
                if (Key >= SortMapCount) Key = SortMapCount - 1;
                break;
            case 0x4b:  //←
                Key--;
                if (Key < 0) Key = 0;
                break;
            case 0x50:  //↓
                SortKeyList[SortGetKeyCount] = Key;
                SortGetKeyCount++; Count++;
                break;
            }
            break;
        //バックスペース
        case '\b':
            if (SortGetKeyCount != 0) {
                SortGetKeyCount--; Count--;
                SortKeyList[SortGetKeyCount] = 0;
                setCursorPos(Count * 8, 3);
                printf("                                   ");
                setCursorPos(Count * 8, 3);
            }
            break;
        //エンター
        case 0x0d:
            if (SortGetKeyCount % 2 == 0) {
                Count = SortGetKeyCount;
                SortGetKeyCount = MAXKEY;
            }
            break;
        }
    }
    //入力回数を代入
    SortGetKeyCount = Count;
    printf("\n");
}


/// <summary>
/// 関数名 | SortExecution
/// 詳細　 | 入力したキーに合わせて入れ替える
/// </summary>
void SortExecution() {
    //入れ替え用変数
    char Number = 0;

    setCursorPos(0, 0);
    SortHeadDisplay();
    for (int i = 0; i < SortGetKeyCount / 2; i++) {
        Sleep(1000);
        Number = SortMapList[SortKeyList[i * 2]];
        SortMapList[SortKeyList[i * 2]] = SortMapList[SortKeyList[i * 2 + 1]];
        SortMapDisplay(SortKeyList[i * 2]);
        Sleep(1000);
        SortMapList[SortKeyList[i * 2 + 1]] = Number;
        SortMapDisplay(SortKeyList[i * 2 + 1]);
    }
}


/// <summary>
/// 関数名 | SortJudge
/// 詳細　 | ゲームのクリア判定
/// </summary>
void SortJudge() {
    int JudgeCount = 0;
    SortKeyDisplay();
    for (int i = 0; i < SortGetKeyCount; i++) {
        if (SortMapList[i] == i + 48) JudgeCount++;
    }
    if (JudgeCount == SortGetKeyCount) TxtLoad(GAMECLEARTXT);
    else TxtLoad(GAMEFAILURE);
    if (getchar() != '\n');
}


/// <summary>
/// 関数名 | SortGame
/// 詳細　 | ソートゲームの全実行
/// </summary>
/// <param name="SortSlcNum">ステージ番号</param>
void SortGame(int SortSlcNum) {
    //選択したステージを読み込み
    SortMapLoad(SortSlcNum);

    SortHeadDisplay();
    SortKeyGet();

    //入力がある場合
    if (SortGetKeyCount != 0) {
        SortExecution();
        SortJudge();
    }
}
