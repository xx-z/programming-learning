/*****************************************************************************************************
*
*   main関数
*   シーン切り替え
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

//ゲームの数
#define MAXGAMENUMBER 2

//アルゴリズムゲームの数
#define MAXALGORITHMNUMBER 4

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
            printf(" ■■■GameSelect■■■\n\n");
            printf("　□ Algorithm Game □\n　□　　  Sort Game □\n　□ 　　　　　Exit □");
            GameSlcNum = Select(MAXGAMENUMBER + 1);
            if (GameSlcNum == 0) Scene = 1;                 //アルゴリズムゲーム
            if (GameSlcNum == 1) Scene = 2;                 //ソートゲーム
            if (GameSlcNum == 2) Scene = 3;                 //終了
            break;

         //アルゴリズムゲーム
        case 1:
            printf("■AlgorithmSelect■\n\n");
            for (int i = 0; i < MAXALGORITHMNUMBER; i++) printf("　□ stage : %d □\n", i);
            printf("　□ 　　 back □");
            AlgoSlcNum = Select(MAXALGORITHMNUMBER + 1);

            if (AlgoSlcNum == MAXALGORITHMNUMBER) {     //ゲームselect画面に戻る
                Scene = 0;
            } else {                                      //アルゴリズムゲーム起動（algorithm.c）
                AlgorithmGame(AlgoSlcNum);
            }
            system("cls");
            break;

         //ソートゲーム
        case 2:
            system("cls");
            printf("coming soon");
            if (getchar() == '\n');
            Scene = 0;
            system("cls");
            break;

        //ゲーム終了
        case 3:
            exit(1);
            break;
        }
    }
}