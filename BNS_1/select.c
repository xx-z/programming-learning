/*****************************************************************************************************
*
*   �Z���N�g��ʁA�I���̖��L�[�\��
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>


/// <summary>
/// �֐��� | SelectDisplay
/// �ڍׁ@ | SlcNum�̒l�����ɖ��̕\��
/// �@�@�@ | ���ȊO�̓X�y�[�X�ŏ㏑�����Ė��i���ɕ\������Ă������́j������
/// </summary>
/// <param name="SlcNum">�I��������</param>
/// <param name="MaxNumber">�Z���N�g�̐�</param>
void SelectDisplay(SlcNum, MaxNumber) {
    setCursorPos(0, 2);
    for (int i = 0; i < MaxNumber; i++) {
        if (i == SlcNum) printf("�@��");
        else printf("�@�@");
        printf("\n");
    }
}


/// <summary>
/// �֐��� | Select
/// �ڍׁ@ | ���L�[�i�㉺�j�ɍ��킹��SlcNum�i�Z���N�g�i���o�[�j��ϓ�
/// �@�@�@ | MaxNumber�ŃZ���N�g�i���o�[�𐧌�
/// </summary>
/// <param name="MaxNumber">�Z���N�g�̐�</param>
/// <returns>�Z���N�g�����l</returns>
int Select(MaxNumber) {
    //�Z���N�g�i���o�[
    int SlcNum = 0;
    //while���̃t���O�ϐ�
    int Flg = 1;

    while (Flg == 1) {
        SelectDisplay(SlcNum, MaxNumber);
        switch (getch()) {
        case 0xe0:
            switch (getch()) {
            case 0x48: SlcNum--; break;
            case 0x50: SlcNum++; break;
            }
            //MaxNumber�ɂ���Đ���
            if (SlcNum < 0) SlcNum = MaxNumber - 1;
            if (SlcNum > MaxNumber - 1) SlcNum = 0;
            break;
        //�G���^�[�i���͏I���j
        case 0x0d:
            Flg = 0;
            break;
        }
    }
    system("cls");
    return SlcNum;
}