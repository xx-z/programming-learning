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

int Target = 0;


/// <summary>
/// 関数名 | AlgoMapLoad
/// 詳細　 | MapFile（マップファイル）のマップを読み込み
/// 　　　 | MapList（マップ行列）に代入
/// 　　　 | マップの最大サイズ計測（MapSizeX, Y）
/// </summary>
/// <param name="MapFile">マップファイルの名前</param>
void AlgoMapLoad(char MapFile[25]) {
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
/// 　　　 | NOPLACE-0: 通っていない場所　OKPLACE-1: 通った場所　PLAYER-2: プレーヤー　WALL-3: 壁
/// 　　　 | プレーヤー(2)の場所は表示する際に、通った場所(1)に変更
/// </summary>
void AlgoMapDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    setCursorPos(0, EXPLAIN_INTERVAL);
    //マップのサイズ分表示
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if (j == 0) printf("　　");
            if (NOPLACE == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("□");
            }
            else if (OKPLACE == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_RED);
                printf("■");
            }
            else if (PLAYER == MapList[j][i]) {
                PlayerPosX = j; PlayerPosY = i;
                //通った場所に変更
                MapList[j][i] = '1';
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("　");
            }
            else if (WALL == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("　");
            }
        }
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf("\n");
    }
    printf("\n▽ 入力 ▽\n");
}


/// <summary>
/// 関数名 | AlgoKeyGet
/// 詳細　 | 入力キーをKeyListに代入
/// 　　　 | 矢印キー : 代入　バックスペース : 取り消し　エンター : 終了　エスケープ：戻る
/// 　　　 | 矢印キー　上 : 1　2 : 右　3 : 下　4 : 左
/// </summary>
void AlgoKeyGet() {
    int Key = 0;                                         //キーの種類
    int Count = 0;                                      //入力回数
    GetKeyCount = 0;
    for (int i = 0; i < MAXKEY; i++) KeyList[i] = 0;

    //入力したキーをKeyListに代入
    while (GetKeyCount != MAXKEY) {
        switch (getch()) {
        case ARROW:
            switch (getch()) {
            case UP: Key = 1; printf("↑"); break;
            case RIGHT: Key = 2; printf("→"); break;
            case DOWN: Key = 3; printf("↓"); break;
            case LEFT: Key = 4; printf("←"); break;
            }
            SoundType();
            KeyList[GetKeyCount] = Key;
            GetKeyCount++; Count++;
            break;
        case BACKSPACE:
            if (GetKeyCount != 0) {
                SoundTypeCancel();
                GetKeyCount--; Count--;
                KeyList[GetKeyCount] = 0;
                setCursorPos(Count * 2, MapSizeY + MAP_INTERVAL);
                printf("　");
                setCursorPos(Count * 2, MapSizeY + MAP_INTERVAL);
            }
            break;
        case ENTER:
            if (GetKeyCount != 0) {
                SoundTypeCancel();
                Count = GetKeyCount;
                GetKeyCount = MAXKEY;
            }
            break;
        case ESC:
            PlaySound(TEXT("data/sound/type_cancel.wav"), NULL, SND_ASYNC);
            Count = 0;
            GetKeyCount = MAXKEY;
            break;
        }
    }
    //入力回数を代入
    GetKeyCount = Count;
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
/// 　　　 | NOPLACE-0: 通っていない場所　OKPLACE-1: 通った場所　PLAYER-2: プレーヤー　WALL-3: 壁
/// </summary>
void AlgoExecution() {
    for (int i = 0; i < GetKeyCount; i++) {
        //壁にぶつかっていない時
        while (MapList[PlayerPosX][PlayerPosY] != WALL) {
            //入力キーに合わせて１つ移動
            switch (KeyList[i]) {
            case 1: PlayerPosY--; break;
            case 2: PlayerPosX++; break;
            case 3: PlayerPosY++; break;
            case 4: PlayerPosX--; break;
            }
            //壁に当たっていない時
            if (MapList[PlayerPosX][PlayerPosY] != WALL) {
                //通ってない場所ならジャッジカウントを減らす
                if (MapList[PlayerPosX][PlayerPosY] == NOPLACE) JudgeCount--;
                MapList[PlayerPosX][PlayerPosY] = PLAYER;
                AlgoMapDisplay();
            }
            //壁に当たった時（キーの画面だけリセット）
            else {
                setCursorPos(0, MapSizeY + MAP_INTERVAL);
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
/// 詳細　 | 入力キーがあるかの確認
/// 　　　 | JudgeCountが0の時にクリア
/// </summary>
void AlgoJudge() {
    printf("\n\n");
    //成功
    if (JudgeCount == 0) {
        TxtLoad(GAMECLEARTXT);
        SoundClear();
    }
    //失敗
    else {
        TxtLoad(GAMEFAILURE);
        SoundFailure();
    }
}


/// <summary>
/// 関数名 | AlgorithmGame
/// 詳細　 | アルゴリズムゲームの全実行内容
/// </summary>
/// <param name="AlgoSlcNum">ステージの番号</param>
void AlgorithmGame(AlgoSlcNum) {
    int FlgLoop = 1;
    int FlgBotton = 1;

    int num[100];
    int ret;
    while (FlgLoop == 1) {
        FlgBotton = 1;
        FlgLoop = 1;
        //説明
        TxtLoad(EXPLAIN);

        //ステージ選択に合わせたマップの読み込み
        char MapFile[25];
        snprintf(MapFile, 25, "data/AlgoMap/map_%d.txt", AlgoSlcNum);
        AlgoMapLoad(MapFile);

        //マップ表示
        AlgoMapDisplay();

        //ScoreW(AlgoSlcNum);

        //キーを入力
        AlgoKeyGet();

        //入力がある場合、実行
        if (GetKeyCount != 0) {
            //実行
            AlgoExecution();

            //結果判定
            AlgoJudge();

            //再度やるか確認
            setCursorPos(0, MapSizeY + 20);
            printf("　戻る：ESC　　もう一度：Backspace");
            while (FlgBotton == 1) {
                switch (getch()) {
                case BACKSPACE:
                    SoundTypeCancel();
                    FlgBotton = 0;
                    system("cls");
                    break;
                case ESC:
                    SoundTypeCancel();
                    FlgBotton = 0;
                    FlgLoop = 0;
                    break;
                }
            }
        }
        else {
            FlgLoop = 0;
        }
    }
}