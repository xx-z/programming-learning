/*****************************************************************************************************
*
*　セレクト画面
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

int Number = 0;


/*****************************************************************************************************
* 関数名 | SelectAlgorithmDisplay
* 概要　 | セレクトの矢印の表示
* 引数　 | SlcNum
* 戻り値 | なし
* 詳細　 | アルゴリズムゲームの矢印の表示
*****************************************************************************************************/
void SelectDisplay(SlcNum) {
    setCursorPos(0, 2);
    for (int i = 0; i < Number; i++) {
        if (i == SlcNum) printf("→");
        else printf("　");
        printf("\n");
    }
}


/*****************************************************************************************************
* 関数名 | SelectAlgorithm
* 概要　 | アルゴリズムセレクト関数
* 引数　 | なし
* 戻り値 | なし
* 詳細　 | 矢印キーに合わせてSlcNum（セレクトナンバーを変動）
*****************************************************************************************************/
int Select(GameNumber) {
    Number = GameNumber;
    int SlcNum = 0;                     //セレクトナンバー
    int Flg = 1;                            //while文のフラグ変数

    while (Flg == 1) {
        SelectDisplay(SlcNum);
        switch (getch()) {
        case 0xe0:
            switch (getch()) {
            case 0x48: SlcNum--; break;
            case 0x50: SlcNum++; break;
            }
            if (SlcNum < 0) SlcNum = 0;
            if (SlcNum > Number - 1) SlcNum = Number - 1;
            break;
        case 0x0d:
            Flg = 0;
            break;
        }
    }
    system("cls");
    return SlcNum;
}