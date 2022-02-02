/*****************************************************************************************************
*
*   セレクト画面、選択の矢印キー表示
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>


/// <summary>
/// 関数名 | SelectDisplay
/// 詳細　 | SlcNumの値を元に矢印の表示
/// 　　　 | 矢印以外はスペースで上書きして矢印（元に表示されていたもの）を消す
/// </summary>
/// <param name="SlcNum">選択した数</param>
/// <param name="MaxNumber">セレクトの数</param>
void SelectDisplay(SlcNum, MaxNumber) {
    setCursorPos(0, 2);
    for (int i = 0; i < MaxNumber; i++) {
        if (i == SlcNum) printf("　→");
        else printf("　　");
        printf("\n");
    }
}


/// <summary>
/// 関数名 | Select
/// 詳細　 | 矢印キー（上下）に合わせてSlcNum（セレクトナンバー）を変動
/// 　　　 | MaxNumberでセレクトナンバーを制限
/// </summary>
/// <param name="MaxNumber">セレクトの数</param>
/// <returns>セレクトした値</returns>
int Select(MaxNumber) {
    //セレクトナンバー
    int SlcNum = 0;
    //while文のフラグ変数
    int Flg = 1;

    while (Flg == 1) {
        SelectDisplay(SlcNum, MaxNumber);
        switch (getch()) {
        case 0xe0:
            switch (getch()) {
            case 0x48: SlcNum--; break;
            case 0x50: SlcNum++; break;
            }
            //MaxNumberによって制限
            if (SlcNum < 0) SlcNum = MaxNumber - 1;
            if (SlcNum > MaxNumber - 1) SlcNum = 0;
            break;
        //エンター（入力終了）
        case 0x0d:
            Flg = 0;
            break;
        }
    }
    system("cls");
    return SlcNum;
}