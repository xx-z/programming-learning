/*****************************************************************************************************
*
*   main�֐�
*   �V�[���؂�ւ�
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

//�Q�[���̐�
#define MAXGAMENUMBER 2

//�A���S���Y���Q�[���̐�
#define MAXALGORITHMNUMBER 4

//�X�^�[�g��ʂ̃e�L�X�g
#define STARTTXT 0


/// <summary>
/// �֐��� | setCursorPos
/// �ڍׁ@ | �w��̏ꏊ�܂œ��͂����Z�b�g
/// �@�@�@ | �\���������̂͏㏑������܂Ŏc��
/// </summary>
/// <param name="x">�R���\�[����X���W</param>
/// <param name="y">�R���\�[����Y���W</param>
void setCursorPos(int x, int y) {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}


/// <summary>
/// �֐��� | main
/// �ڍׁ@ | �X�^�[�g��ʂ̕\��
/// �@�@�@ | �V�[���؂�ւ�
/// �@�@�@ | �i0:�Q�[���Z���N�g��� 1:�A���S���Y���Q�[�� 2:�\�[�g�Q�[�� 3:�Q�[���I���j
/// �@�@�@ | �I���f�[�^�̊Ǘ�
/// </summary>
void main() {
    //�V�[���؂�ւ��ϐ�
    int Scene = 0;
    //�Q�[���̃Z���N�g�i���o�[
    int GameSlcNum = 0;
    //�A���S���Y���Q�[���̃Z���N�g�i���o�[
    int AlgoSlcNum = 0;

    //�X�^�[�g��ʁi�h�b�g�ŕ�����\���j
    TxtLoad(STARTTXT);
    printf("\n\n�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@press enter");
    if (getchar() == '\n');
    system("cls");

    //�V�[���؂�ւ�
    while (1) {
        switch (Scene) {

        //�Q�[���Z���N�g���
        case 0:
            printf(" ������GameSelect������\n\n");
            printf("�@�� Algorithm Game ��\n�@���@�@  Sort Game ��\n�@�� �@�@�@�@�@Exit ��");
            GameSlcNum = Select(MAXGAMENUMBER + 1);
            if (GameSlcNum == 0) Scene = 1;                 //�A���S���Y���Q�[��
            if (GameSlcNum == 1) Scene = 2;                 //�\�[�g�Q�[��
            if (GameSlcNum == 2) Scene = 3;                 //�I��
            break;

         //�A���S���Y���Q�[��
        case 1:
            printf("��AlgorithmSelect��\n\n");
            for (int i = 0; i < MAXALGORITHMNUMBER; i++) printf("�@�� stage : %d ��\n", i);
            printf("�@�� �@�@ back ��");
            AlgoSlcNum = Select(MAXALGORITHMNUMBER + 1);

            if (AlgoSlcNum == MAXALGORITHMNUMBER) {     //�Q�[��select��ʂɖ߂�
                Scene = 0;
            } else {                                      //�A���S���Y���Q�[���N���ialgorithm.c�j
                AlgorithmGame(AlgoSlcNum);
            }
            system("cls");
            break;

         //�\�[�g�Q�[��
        case 2:
            system("cls");
            printf("coming soon");
            if (getchar() == '\n');
            Scene = 0;
            system("cls");
            break;

        //�Q�[���I��
        case 3:
            exit(1);
            break;
        }
    }
}