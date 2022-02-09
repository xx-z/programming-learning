/*****************************************************************************************************
*
*   セレクト画面、選択の矢印キー表示
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

#define ENTER 0x0d
#define ARROW 0xe0
#define UP 0x50
#define DOWN 0x48

//矢印までの距離
#define ARROW_INTERVAL_X 2
#define ARROW_INTERVAL_Y 3

/// <summary>
/// 関数名 | SelectDisplay
/// 詳細　 | スペースで上書きして矢印（元に表示されていたもの）を消す
/// 　　　 | SlcNumの値を元に矢印の表示
/// </summary>
/// <param name="SlcNum">選択した数</param>
/// <param name="MaxNumber">セレクトの数</param>
void SelectDisplay(SlcNum, MaxNumber) {
    for (int i = 0; i < MaxNumber; i++) {
        setCursorPos(ARROW_INTERVAL_X, i + ARROW_INTERVAL_Y);
        printf("　");
    }
    setCursorPos(ARROW_INTERVAL_X, SlcNum + ARROW_INTERVAL_Y);
    printf("→");
    setCursorPos(0, 0);
}


/// <summary>
/// 関数名 | Select
/// 詳細　 | 矢印キー（上下）に合わせてSlcNum（セレクトナンバー）を変動
/// 　　　 | MaxNumberでセレクトナンバーを制限
/// </summary>
/// <param name="MaxNumber">セレクトの数</param>
/// <param name="SlcNum">現在セレクトしている数</param>
/// <returns>セレクトした値</returns>
int Select(MaxNumber, SlcNum) {
    //while文のフラグ変数
    int Flg = 1;

    while (Flg == 1) {
        SelectDisplay(SlcNum, MaxNumber);
        switch (getch()) {
        case ARROW:
            switch (getch()) {
            case DOWN: SlcNum--; break;
            case UP: SlcNum++; break;
            }
            SoundType();
            //MaxNumberによって制限
            if (SlcNum < 0) SlcNum = MaxNumber - 1;
            if (SlcNum > MaxNumber - 1) SlcNum = 0;
            break;
        case ENTER:
            SoundBotton();
            Flg = 0;
            break;
        }
    }
    system("cls");
    return SlcNum;
}