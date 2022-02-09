/*****************************************************************************************************
*
*　テキストの読み込み、ドット絵を表現する（スタート画面、クリア、失敗）
*
*****************************************************************************************************/

#include <stdio.h>
#include  <Windows.h>

#define  T_WHITE 0x0f
#define COL_BLUE 0x09
#define  T_RED 0x0c


/// <summary>
/// 関数名 | TxtLoad
/// 詳細　 | 指定の行数の間の文字を読み込み
/// 　　　 | ドット文字を表示
/// 　　　 | 色の付いたブロックの表示など
/// </summary>
/// <param name="Line">行数指定</param>
void TxtLoad(int Line) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    const char* file = "data/Dot.txt";
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
        if (Line * 10 <= LineCount && LineCount < (Line + 1) * 10) {
            if ('8' == c) { //青文字
                SetConsoleTextAttribute(hStdoutHandle, COL_BLUE);
                printf("■");
            }
            else if ('0' == c) { //白文字（四角）
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("□");
            }
            else if ('1' == c) { //赤文字
                SetConsoleTextAttribute(hStdoutHandle, T_RED);
                printf("■");
            }
            else if ('2' == c) { //薄い青背景
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("　");
            }
            else if ('3' == c) { //明るい白背景
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("　");
            }
            else if ('4' == c) { //明るい青背景
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf(" ");
            }
            else if ('5' == c) { //明るい赤背景
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_RED | BACKGROUND_INTENSITY);
                printf(" ");
            }
            else { //白文字
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("%c", c);
            }
        }
        if ('\n' == c) LineCount++;         //行数回数計算
    }
    //色を初期化
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
    fclose(fp);
}