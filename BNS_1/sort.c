/*****************************************************************************************************
*
*   �\�[�g�Q�[��
*   
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
#include <string.h>
#include "sort.h"


//���̓L�[�̃��X�g
int SortKeyList[MAXKEY] = { 0 };
//�\�[�g�̃}�b�v���X�g
int SortMapList[MAXMAP] = { 0 };

//�L�[�̓��͉�
int SortGetKeyCount = 0;
//�\�[�g�}�b�v�̃T�C�Y
int SortMapCount = 0;


/// <summary>
/// �֐��� | SortMapLoad
/// �ڍׁ@ | �s���i�X�e�[�W�j�ɍ��킹���}�b�v�̓ǂݍ���
/// </summary>
/// <param name="Line">�ǂݍ��ލs��</param>
void SortMapLoad(int Line) {
    const char* file = "data/sort_map.txt";
    FILE* fp;
    char c;
    //�s���̉�
    int LineCount = 0;
    //�\�[�g�}�b�v�̃T�C�Y�����Z�b�g
    SortMapCount = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("\n�t�@�C���G���[\n%s�̃I�[�v���Ɏ��s���܂����B\n", file);
        exit(1);
    }
    //EOF�܂Ńt�@�C�����當����1�������ǂݍ���
    while ((c = fgetc(fp)) != EOF) {
        if ('\n' == c) LineCount++;
        if (Line == LineCount && '\n' != c) {
            SortMapList[SortMapCount] = c;
            SortMapCount++;
        }
    }
    fclose(fp);
}

/// <summary>
/// �֐��� | SortHeadDisplay
/// �ڍׁ@ | �����ƂȂ��̕\��
/// �@�@�@ | �����̓u���b�N�ƂȂ�悤�ɐF�t������
/// </summary>
void SortHeadDisplay() {
    setCursorPos(1, EXPLAIN_INTERVAL);
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < SortMapCount; i++) {
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf(" ");
        SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
        printf(" %d ", i);
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
    printf(" ");
}


/// <summary>
/// �֐��� | SortMapDisplay
/// �ڍׁ@ | �\�[�g�}�b�v�̕\��
/// �@�@�@ | ���̓L�[�ɍ��킹�ĐF�t������
/// </summary>
/// <param name="Key">�\�[�g�}�b�v�̕\��</param>
void SortMapDisplay(int Key) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    setCursorPos(2, MAP_INTERVAL);
    for (int i = 0; i < SortMapCount; i++) {
        if (Key == i) {
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_RED | BACKGROUND_INTENSITY | T_WHITE);
        }
        else {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        }
        printf(" %c ", SortMapList[i]);
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf(" ");
    }
    printf("\n\n");
}


/// <summary>
/// �֐��� | SortKeyDisplay
/// �ڍׁ@ | �I�������L�[��\������
/// </summary>
void SortKeyDisplay() {
    printf("�� ���� ��\n");
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < SortGetKeyCount; i++) {
        if (i % 2 == 0) {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(" (");
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
            printf(" %d ", SortKeyList[i]);
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(" ��");
        }
        else {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(" ");
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
            printf(" %d ", SortKeyList[i]);
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
            printf(") ��");
        }
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
}


/// <summary>
/// �֐��� | SortKeyGet
/// �ڍׁ@ | �L�[���͂��L�[���X�g�iSortKeyList[]�j�ɑ������
/// </summary>
void SortKeyGet() {
    int Key = 0;                                         //�L�[�̎��
    int Count = 0;                                      //���͉�
    //������
    SortGetKeyCount = 0;
    for (int i = 0; i < MAXKEY; i++) SortKeyList[i] = 0;

    //���͂����L�[��KeyList�ɑ��
    while (SortGetKeyCount != MAXKEY) {
        //�}�b�v�ƃL�[��\��
        SortMapDisplay(Key);
        SortKeyDisplay();

        switch (getch()) {
        case ARROW:
            switch (getch()) {
            case RIGHT:  //��
                Key++;
                if (Key >= SortMapCount) Key = SortMapCount - 1;
                break;
            case LEFT:  //��
                Key--;
                if (Key < 0) Key = 0;
                break;
            case DOWN:  //��
                SoundType();
                SortKeyList[SortGetKeyCount] = Key;
                SortGetKeyCount++; Count++;
                break;
            }
            break;
        case BACKSPACE:
            if (SortGetKeyCount != 0) {
                SoundTypeCancel();
                SortGetKeyCount--; Count--;
                SortKeyList[SortGetKeyCount] = 0;
                setCursorPos(Count * 8, KEY_INTERVAL);
                printf("                                   ");
                setCursorPos(Count * 8, KEY_INTERVAL);
            }
            break;
        case ENTER:
            if (SortGetKeyCount % 2 == 0 && SortGetKeyCount != 0) {
                SoundTypeCancel();
                Count = SortGetKeyCount;
                SortGetKeyCount = MAXKEY;
            }
            break;
        case ESC:
            SoundTypeCancel();
            Count = 0;
            SortGetKeyCount = MAXKEY;
            break;
        }
    }
    //���͉񐔂���
    SortGetKeyCount = Count;
    printf("\n");
}


/// <summary>
/// �֐��� | SortExecution
/// �ڍׁ@ | ���͂����L�[�ɍ��킹�ē���ւ���
/// </summary>
void SortExecution() {
    //����ւ��p�ϐ�
    char Number = 0;

    setCursorPos(0, 0);
    SortHeadDisplay();
    for (int i = 0; i < SortGetKeyCount / 2; i++) {
        Sleep(300);
        Number = SortMapList[SortKeyList[i * 2]];
        SortMapList[SortKeyList[i * 2]] = SortMapList[SortKeyList[i * 2 + 1]];
        SortMapDisplay(SortKeyList[i * 2]);
        Sleep(300);
        SortMapList[SortKeyList[i * 2 + 1]] = Number;
        SortMapDisplay(SortKeyList[i * 2 + 1]);
    }
}


/// <summary>
/// �֐��� | SortJudge
/// �ڍׁ@ | �Q�[���̃N���A����
/// </summary>
void SortJudge() {
    int JudgeCount = 0;
    SortKeyDisplay();
    for (int i = 0; i < SortMapCount; i++) {
        if (SortMapList[i] == i + 48) JudgeCount++;
    }
    printf("\n\n");
    if (JudgeCount == SortMapCount) {
        TxtLoad(GAMECLEARTXT);
        SoundClear();
    }
    else {
        TxtLoad(GAMEFAILURE);
        SoundFailure();
    }
}


/// <summary>
/// �֐��� | SortGame
/// �ڍׁ@ | �\�[�g�Q�[���̑S���s
/// </summary>
/// <param name="SortSlcNum">�X�e�[�W�ԍ�</param>
void SortGame(int SortSlcNum) {
    int FlgLoop = 1;
    int FlgBotton = 1;
    while (FlgLoop == 1) {
        FlgBotton = 1;
        FlgLoop = 1;
        TxtLoad(EXPLAIN);

        //�I�������X�e�[�W��ǂݍ���
        SortMapLoad(SortSlcNum);

        SortHeadDisplay();
        SortKeyGet();

        //���͂�����ꍇ
        if (SortGetKeyCount != 0) {
            //���s
            SortExecution();

            //���ʔ���
            SortJudge();

            //�ēx��邩�m�F
            setCursorPos(0, 22);
            printf("�@�߂�FESC�@�@������x�FBackspace");
            while (FlgBotton == 1) {
                switch (getch()) {
                case BACKSPACE:
                    PlaySound(TEXT("data/sound/type_cancel.wav"), NULL, SND_ASYNC);
                    FlgBotton = 0;
                    system("cls");
                    break;
                case ESC:
                    PlaySound(TEXT("data/sound/type_cancel.wav"), NULL, SND_ASYNC);
                    FlgBotton = 0;
                    FlgLoop = 0;
                    break;
                }
            }
        }
        else {
            FlgLoop = 0;
        }
    }
}
