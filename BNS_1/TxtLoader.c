/*****************************************************************************************************
*
*　テキストのドット読み込み
*
*****************************************************************************************************/

#include <stdio.h>
#include  <Windows.h>

#define  T_WHITE 0x0f
#define COL_BLUE 0x09


/// <summary>
/// 関数名 | TxtLoad
/// 詳細　 | 指定の行数の間の文字を読み込み
/// 　　　 | ドット文字を表示
/// 　　　 | （スタート画面、ゲームクリア、ゲーム失敗の表示）
/// </summary>
/// <param name="Line">行数指定</param>
void TxtLoad(int Line) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    const char* file = "Dot.txt";
    FILE* fp;
    char c;
    //行数の回数
    int LineCount = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("\nファイルエラー\n%sのオープンに失敗しました。\n", file);
        exit(1);
    }
    //EOFまでファイルから文字を1文字ずつ読み込む
    while ((c = fgetc(fp)) != EOF) {
        if ('\n' == c) LineCount++;         //行数回数計算
        if (Line * 10 <= LineCount && LineCount < (Line + 1) * 10) {
            if ('8' == c) {         //文字あり
                SetConsoleTextAttribute(hStdoutHandle, COL_BLUE);
                printf("■");
            }
            else if ('\n' == c) {
                printf("%c", c);
            }
            else {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("□");
            }
        }
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
    fclose(fp);
}