/*****************************************************************************************************
*
*�@�e�L�X�g�̃h�b�g�ǂݍ���
*
*****************************************************************************************************/

#include <stdio.h>
#include  <Windows.h>

#define  T_WHITE 0x0f
#define COL_BLUE 0x09


/// <summary>
/// �֐��� | TxtLoad
/// �ڍׁ@ | �w��̍s���̊Ԃ̕�����ǂݍ���
/// �@�@�@ | �h�b�g������\��
/// �@�@�@ | �i�X�^�[�g��ʁA�Q�[���N���A�A�Q�[�����s�̕\���j
/// </summary>
/// <param name="Line">�s���w��</param>
void TxtLoad(int Line) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    const char* file = "Dot.txt";
    FILE* fp;
    char c;
    //�s���̉�
    int LineCount = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("\n�t�@�C���G���[\n%s�̃I�[�v���Ɏ��s���܂����B\n", file);
        exit(1);
    }
    //EOF�܂Ńt�@�C�����當����1�������ǂݍ���
    while ((c = fgetc(fp)) != EOF) {
        if ('\n' == c) LineCount++;         //�s���񐔌v�Z
        if (Line * 10 <= LineCount && LineCount < (Line + 1) * 10) {
            if ('8' == c) {         //��������
                SetConsoleTextAttribute(hStdoutHandle, COL_BLUE);
                printf("��");
            }
            else if ('\n' == c) {
                printf("%c", c);
            }
            else {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("��");
            }
        }
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
    fclose(fp);
}