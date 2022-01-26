/*****************************************************************************************************
*
*�@�Z���N�g���
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

int Number = 0;


/*****************************************************************************************************
* �֐��� | SelectAlgorithmDisplay
* �T�v�@ | �Z���N�g�̖��̕\��
* �����@ | SlcNum
* �߂�l | �Ȃ�
* �ڍׁ@ | �A���S���Y���Q�[���̖��̕\��
*****************************************************************************************************/
void SelectDisplay(SlcNum) {
    setCursorPos(0, 2);
    for (int i = 0; i < Number; i++) {
        if (i == SlcNum) printf("��");
        else printf("�@");
        printf("\n");
    }
}


/*****************************************************************************************************
* �֐��� | SelectAlgorithm
* �T�v�@ | �A���S���Y���Z���N�g�֐�
* �����@ | �Ȃ�
* �߂�l | �Ȃ�
* �ڍׁ@ | ���L�[�ɍ��킹��SlcNum�i�Z���N�g�i���o�[��ϓ��j
*****************************************************************************************************/
int Select(GameNumber) {
    Number = GameNumber;
    int SlcNum = 0;                     //�Z���N�g�i���o�[
    int Flg = 1;                            //while���̃t���O�ϐ�

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