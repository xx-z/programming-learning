/*****************************************************************************************************
*
*   main�֐��A�V�[���؂�ւ�
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

//�Q�[���̐�
#define MAXGAMENUMBER 2

//�A���S���Y���Q�[���̐�
#define MAXALGORITHMNUMBER 4

//�\�[�g�Q�[���̐�
#define MAXSORTNUMBER 4

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
    //�\�[�g�Q�[���̃Z���N�g�i���o�[
    int SortSlcNum = 0;

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
            printf("�@�@��������Game Select��������\n\n");
            printf("�@�@�� Algorithm Puzzle Game ��\n�@�@�� Algorithm Sort   Game ��\n�@�@�� �@�@�@�@�@�@�@�@ Exit ��");
            GameSlcNum = Select(MAXGAMENUMBER + 1);
            if (GameSlcNum == 0) Scene = 1;                 //�A���S���Y���Q�[��
            if (GameSlcNum == 1) Scene = 2;                 //�\�[�g�Q�[��
            if (GameSlcNum == 2) Scene = 3;                 //�I��
            break;

         //�A���S���Y���Q�[��
        case 1:
            //�I����ʕ\��
            printf("��Algorithm Puzzle Select��\n\n");
            for (int i = 0; i < MAXALGORITHMNUMBER; i++) printf("�@�@�� stage : %d ��\n", i);
            printf("�@�@�� �@�@ back ��");
            //���L�[�\��
            AlgoSlcNum = Select(MAXALGORITHMNUMBER + 1);
            //back�{�^����I���A�Q�[��select��ʂɖ߂�
            if (AlgoSlcNum == MAXALGORITHMNUMBER) Scene = 0;
            //�X�e�[�W��I���A�A���S���Y���Q�[���N���ialgorithm.c�j
            else AlgorithmGame(AlgoSlcNum);
            system("cls");
            break;

         //�\�[�g�Q�[���i�܂�����i�K�j
        case 2:
            printf("��Algorithm Sort Select��\n\n");
            for (int i = 0; i < MAXSORTNUMBER; i++) printf("�@�@�� stage : %d ��\n", i);
            printf("�@�@�� �@�@ back ��");
            SortSlcNum = Select(MAXSORTNUMBER + 1);
            //�Q�[��select��ʂɖ߂�
            if (SortSlcNum == MAXSORTNUMBER) Scene = 0;
            //�X�e�[�W��I���A�\�[�g�Q�[���N���isort.c�j
            else SortGame(SortSlcNum);

            system("cls");
            break;

        //�Q�[���I��
        case 3:
            exit(1);
            break;
        }
    }
}