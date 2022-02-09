/*****************************************************************************************************
*
*�@�e�L�X�g�̓ǂݍ��݁A�h�b�g�G��\������i�X�^�[�g��ʁA�N���A�A���s�j
*
*****************************************************************************************************/

#include <stdio.h>
#include  <Windows.h>

#define  T_WHITE 0x0f
#define COL_BLUE 0x09
#define  T_RED 0x0c


/// <summary>
/// �֐��� | TxtLoad
/// �ڍׁ@ | �w��̍s���̊Ԃ̕�����ǂݍ���
/// �@�@�@ | �h�b�g������\��
/// �@�@�@ | �F�̕t�����u���b�N�̕\���Ȃ�
/// </summary>
/// <param name="Line">�s���w��</param>
void TxtLoad(int Line) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    const char* file = "data/Dot.txt";
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
        if (Line * 10 <= LineCount && LineCount < (Line + 1) * 10) {
            if ('8' == c) { //����
                SetConsoleTextAttribute(hStdoutHandle, COL_BLUE);
                printf("��");
            }
            else if ('0' == c) { //�������i�l�p�j
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("��");
            }
            else if ('1' == c) { //�ԕ���
                SetConsoleTextAttribute(hStdoutHandle, T_RED);
                printf("��");
            }
            else if ('2' == c) { //�����w�i
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("�@");
            }
            else if ('3' == c) { //���邢���w�i
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("�@");
            }
            else if ('4' == c) { //���邢�w�i
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf(" ");
            }
            else if ('5' == c) { //���邢�Ԕw�i
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_RED | BACKGROUND_INTENSITY);
                printf(" ");
            }
            else { //������
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("%c", c);
            }
        }
        if ('\n' == c) LineCount++;         //�s���񐔌v�Z
    }
    //�F��������
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
    fclose(fp);
}