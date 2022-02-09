/*****************************************************************************************************
*
*   �Z���N�g��ʁA�I���̖��L�[�\��
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

#define ENTER 0x0d
#define ARROW 0xe0
#define UP 0x50
#define DOWN 0x48

//���܂ł̋���
#define ARROW_INTERVAL_X 2
#define ARROW_INTERVAL_Y 3

/// <summary>
/// �֐��� | SelectDisplay
/// �ڍׁ@ | �X�y�[�X�ŏ㏑�����Ė��i���ɕ\������Ă������́j������
/// �@�@�@ | SlcNum�̒l�����ɖ��̕\��
/// </summary>
/// <param name="SlcNum">�I��������</param>
/// <param name="MaxNumber">�Z���N�g�̐�</param>
void SelectDisplay(SlcNum, MaxNumber) {
    for (int i = 0; i < MaxNumber; i++) {
        setCursorPos(ARROW_INTERVAL_X, i + ARROW_INTERVAL_Y);
        printf("�@");
    }
    setCursorPos(ARROW_INTERVAL_X, SlcNum + ARROW_INTERVAL_Y);
    printf("��");
    setCursorPos(0, 0);
}


/// <summary>
/// �֐��� | Select
/// �ڍׁ@ | ���L�[�i�㉺�j�ɍ��킹��SlcNum�i�Z���N�g�i���o�[�j��ϓ�
/// �@�@�@ | MaxNumber�ŃZ���N�g�i���o�[�𐧌�
/// </summary>
/// <param name="MaxNumber">�Z���N�g�̐�</param>
/// <param name="SlcNum">���݃Z���N�g���Ă��鐔</param>
/// <returns>�Z���N�g�����l</returns>
int Select(MaxNumber, SlcNum) {
    //while���̃t���O�ϐ�
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
            //MaxNumber�ɂ���Đ���
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