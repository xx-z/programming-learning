/*****************************************************************************************************
*
*�@main�֐�
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

//�Q�[���̐�
#define MAXGAMENUMBER 2

//�A���S���Y���Q�[���̐�
#define MAXALGORITHMNUMBER 4

//�w��̏ꏊ�̉�ʃ��Z�b�g�֐�
void setCursorPos(int x, int y) {
    HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hCons, pos);
}


void main() {
    int Scene = 0;
    int GameSlcNum = 0;                  //�Q�[���̃Z���N�g�i���o�[
    int AlgoSlcNum = 0;                     //�A���S���Y���Q�[���̃Z���N�g�i���o�[

    int Flg = 1;
    //�X�^�[�g��� (start.c)
    StartDisplay();

    while (Flg == 1) {
        switch (Scene) {
        //�Q�[���Z���N�g���
        case 0:
            printf("GameSelect\n\n");
            printf("�@Algorithm Game\n�@Sort Game");
            GameSlcNum = Select(MAXGAMENUMBER);
            if (GameSlcNum == 0) Scene = 1;
            else Scene = 2;
            break;
         //�A���S���Y���Q�[��
        case 1:
            printf("Algorithm Select\n\n");
            printf("�@1\n�@2\n�@3\n�@4\n");
            AlgoSlcNum = Select(MAXALGORITHMNUMBER);
            AlgorithmGame(AlgoSlcNum);
            Flg = 0;
            break;
         //�\�[�g���
        case 2:
            system("cls");
            printf("coming soon");
            Flg = 0;
            break;
        }
    }
}