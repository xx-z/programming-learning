/*****************************************************************************************************
*
*   main関数、シーン切り替え
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

//ゲームの数
#define MAXGAMENUMBER 2

//アルゴリズムゲームの数
#define MAXALGORITHMNUMBER 4

//ソートゲームの数
#define MAXSORTNUMBER 4

//スタート画面のテキスト
#define STARTTXT 0


/// <summary>
/// 関数名 | setCursorPos
/// 詳細　 | 指定の場所まで入力をリセット
/// 　　　 | 表示したものは上書きするまで残る
/// </summary>
/// <param name="x">コンソールのX座標</param>
/// <param name="y">コンソールのY座標</param>
void setCursorPos(int x, int y) {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}


/// <summary>
/// 関数名 | main
/// 詳細　 | スタート画面の表示
/// 　　　 | シーン切り替え
/// 　　　 | （0:ゲームセレクト画面 1:アルゴリズムゲーム 2:ソートゲーム 3:ゲーム終了）
/// 　　　 | 選択データの管理
/// </summary>
void main() {
    //シーン切り替え変数
    int Scene = 0;
    //ゲームのセレクトナンバー
    int GameSlcNum = 0;
    //アルゴリズムゲームのセレクトナンバー
    int AlgoSlcNum = 0;
    //ソートゲームのセレクトナンバー
    int SortSlcNum = 0;

    //スタート画面（ドットで文字を表示）
    TxtLoad(STARTTXT);
    printf("\n\n　　　　　　　　　　　　　　　　　　　　　　　press enter");
    if (getchar() == '\n');
    system("cls");

    //シーン切り替え
    while (1) {
        switch (Scene) {

        //ゲームセレクト画面
        case 0:
            printf("　　■■■■Game Select■■■■\n\n");
            printf("　　□ Algorithm Puzzle Game □\n　　□ Algorithm Sort   Game □\n　　□ 　　　　　　　　 Exit □");
            GameSlcNum = Select(MAXGAMENUMBER + 1);
            if (GameSlcNum == 0) Scene = 1;                 //アルゴリズムゲーム
            if (GameSlcNum == 1) Scene = 2;                 //ソートゲーム
            if (GameSlcNum == 2) Scene = 3;                 //終了
            break;

         //アルゴリズムゲーム
        case 1:
            //選択画面表示
            printf("■Algorithm Puzzle Select■\n\n");
            for (int i = 0; i < MAXALGORITHMNUMBER; i++) printf("　　□ stage : %d □\n", i);
            printf("　　□ 　　 back □");
            //矢印キー表示
            AlgoSlcNum = Select(MAXALGORITHMNUMBER + 1);
            //backボタンを選択、ゲームselect画面に戻る
            if (AlgoSlcNum == MAXALGORITHMNUMBER) Scene = 0;
            //ステージを選択、アルゴリズムゲーム起動（algorithm.c）
            else AlgorithmGame(AlgoSlcNum);
            system("cls");
            break;

         //ソートゲーム（まだ試作段階）
        case 2:
            printf("■Algorithm Sort Select■\n\n");
            for (int i = 0; i < MAXSORTNUMBER; i++) printf("　　□ stage : %d □\n", i);
            printf("　　□ 　　 back □");
            SortSlcNum = Select(MAXSORTNUMBER + 1);
            //ゲームselect画面に戻る
            if (SortSlcNum == MAXSORTNUMBER) Scene = 0;
            //ステージを選択、ソートゲーム起動（sort.c）
            else SortGame(SortSlcNum);

            system("cls");
            break;

        //ゲーム終了
        case 3:
            exit(1);
            break;
        }
    }
}