/*****************************************************************************************************
*
*�@�A���S���Y���Q�[��
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
#include "algorithm.h"

//�L�[���͔z��
int KeyList[MAXKEY] = { 0 };
//�L�[���͉�
int GetKeyCount = 0;

//�}�b�v�̍s�񃊃X�g
char MapList[MAXMAP][MAXMAP];
//�}�b�v��XY�̍ő�T�C�Y
int MapSizeX = 0, MapSizeY = 0;

//���݂̃v���[���[�̍��W
int PlayerPosX = 0, PlayerPosY = 0;

//�W���b�`�J�E���g
int JudgeCount = 0;


/// <summary>
/// �֐��� | AlgoMapLoad
/// �ڍׁ@ | MapFile�i�}�b�v�t�@�C���j�̃}�b�v��ǂݍ���
/// �@�@�@ | MapList�i�}�b�v�s��j�ɑ��
/// �@�@�@ | �}�b�v�̍ő�T�C�Y�v���iMapSizeX, Y�j
/// </summary>
/// <param name="MapFile">�}�b�v�t�@�C���̖��O</param>
void AlgoMapLoad(char MapFile[25]) {
    const char* file = MapFile;
    FILE* fp;
    char c;
    int X = 0, Y = 0;

    //�f�[�^�̏�����
    JudgeCount = 0;
    for (int i = 0; i < MAXMAP; i++) {
        for (int j = 0; j < MAXMAP; j++) {
            MapList[i][j] = '4';
        }
    }

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("\n�t�@�C���G���[\n%s�̃I�[�v���Ɏ��s���܂����B\n", file);
        exit(1);
    }
    //EOF�܂Ńt�@�C�����當����1�������ǂݍ���
    while ((c = fgetc(fp)) != EOF) {
        //�ǂݍ��񂾃f�[�^��񎟌��z���MapList�ɑ��
        if ('\n' == c) {
            if (MapSizeX < X) MapSizeX = X;
            Y++; X = 0;
        }
        else {
            if ('0' == c) JudgeCount++;     //�N���A����Ŏg��0�̌��𐔂���
            MapList[X][Y] = c; X++;
        }
    }
    MapSizeY = Y + 1;
    fclose(fp);
}


/// <summary>
/// �֐��� | AlgoMapDisplay
/// �ڍׁ@ | MapList�i�}�b�v�s��j�̕\��
/// �@�@�@ | NOPLACE-0: �ʂ��Ă��Ȃ��ꏊ�@OKPLACE-1: �ʂ����ꏊ�@PLAYER-2: �v���[���[�@WALL-3: ��
/// �@�@�@ | �v���[���[(2)�̏ꏊ�͕\������ۂɁA�ʂ����ꏊ(1)�ɕύX
/// </summary>
void AlgoMapDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Algorithm Game\n\n");
    //�}�b�v�̃T�C�Y���\��
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if (NOPLACE == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("��");
            }
            else if (OKPLACE == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_RED);
                printf("��");
            }
            else if (PLAYER == MapList[j][i]) {
                PlayerPosX = j; PlayerPosY = i;
                //�ʂ����ꏊ�ɕύX
                MapList[j][i] = '1';
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("�@");
            }
            else if (WALL == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("�@");
            }
        }
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf("\n");
    }
    printf("\n��������������������������������������������������������������������������������\n��������������������������������������������������������������������������������\n\n");
}


/// <summary>
/// �֐��� | AlgoKeyGet
/// �ڍׁ@ | ���̓L�[��KeyList�ɑ��
/// �@�@�@ | ���L�[ : ����@�o�b�N�X�y�[�X : �������@�G���^�[ : �I��
/// �@�@�@ | ���L�[�@�� : 1�@2 : �E�@3 : ���@4 : ��
/// </summary>
void AlgoKeyGet() {
    int Key = 0;                                         //�L�[�̎��
    int Count = 0;                                      //���͉�
    GetKeyCount = 0;
    for (int i = 0; i < MAXKEY; i++) KeyList[i] = 0;

    //���͂����L�[��KeyList�ɑ��
    while (GetKeyCount != MAXKEY) {
        switch (getch()) {

            //���L�[
        case 0xe0:
            switch (getch()) {
            case UP: Key = 1; printf("��"); break;
            case RIGHT: Key = 2; printf("��"); break;
            case DOWN: Key = 3; printf("��"); break;
            case LEFT: Key = 4; printf("��"); break;
            }
            KeyList[GetKeyCount] = Key;
            GetKeyCount++; Count++;
            break;

            //�o�b�N�X�y�[�X
        case '\b':
            if (GetKeyCount != 0) {
                GetKeyCount--; Count--;
                KeyList[GetKeyCount] = 0;
                setCursorPos(Count * 2, MapSizeY + INTERVAL);
                printf("�@");
                setCursorPos(Count * 2, MapSizeY + INTERVAL);
            }
            break;

            //�G���^�[
        case 0x0d:
            Count = GetKeyCount;
            GetKeyCount = MAXKEY;
            break;
        }
    }
    //���͉񐔂���
    GetKeyCount = Count;
    printf("\n");
}


/// <summary>
/// �֐��� | AlgoKeyDisplay
/// �ڍׁ@ | KeyList�i���̓L�[�j�̕\��
/// �@�@�@ | ���s���̖��L�[�̋����\��
/// </summary>
/// <param name="KeyNumber">�L�[���͔z��̑I�����ꂽ�l</param>
void AlgoKeyDisplay(KeyNumber) {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < GetKeyCount; i++) {
        if (KeyNumber == i) {
            SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY | T_WHITE);
        }
        else {
            SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        }
        switch (KeyList[i]) {
        case 1: printf("��"); break;
        case 2: printf("��"); break;
        case 3: printf("��"); break;
        case 4: printf("��"); break;
        }
    }
    SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
}


/// <summary>
/// �֐��� | AlgoExecution
/// �ڍׁ@ | �L�[���͂ɉ����ăv���C���[���ړ������ĕ\��������
/// �@�@�@ | NOPLACE-0: �ʂ��Ă��Ȃ��ꏊ�@OKPLACE-1: �ʂ����ꏊ�@PLAYER-2: �v���[���[�@WALL-3: ��
/// </summary>
void AlgoExecution() {
    for (int i = 0; i < GetKeyCount; i++) {
        //�ǂɂԂ����Ă��Ȃ���
        while (MapList[PlayerPosX][PlayerPosY] != WALL) {
            //���̓L�[�ɍ��킹�ĂP�ړ�
            switch (KeyList[i]) {
            case 1: PlayerPosY--; break;
            case 2: PlayerPosX++; break;
            case 3: PlayerPosY++; break;
            case 4: PlayerPosX--; break;
            }
            //�ǂɓ������Ă��Ȃ���
            if (MapList[PlayerPosX][PlayerPosY] != WALL) {
                //�ʂ��ĂȂ��ꏊ�Ȃ�W���b�W�J�E���g�����炷
                if (MapList[PlayerPosX][PlayerPosY] == NOPLACE) JudgeCount--;
                MapList[PlayerPosX][PlayerPosY] = PLAYER;
                setCursorPos(0, 0);
                AlgoMapDisplay();
            }
            //�ǂɓ����������i�L�[�̉�ʂ������Z�b�g�j
            else {
                setCursorPos(0, MapSizeY + INTERVAL);
            }
            AlgoKeyDisplay(i);
            Sleep(EXECUTIONSPEED);
        }
        //�ǂɂԂ����Ă���̂Ŗ߂�
        switch (KeyList[i]) {
        case 1: PlayerPosY++; break;
        case 2: PlayerPosX--; break;
        case 3: PlayerPosY--; break;
        case 4: PlayerPosX++; break;
        }
    }
}


/// <summary>
/// �֐��� | AlgoJudgement
/// �ڍׁ@ | ���̓L�[�����邩�̊m�F
/// �@�@�@ | JudgeCount��0�̎��ɃN���A
/// </summary>
void AlgoJudge() {
    //����
    if (JudgeCount == 0) TxtLoad(GAMECLEARTXT);
    //���s
    else TxtLoad(GAMEFAILURE);
    if (getchar() != '\n');
}


/// <summary>
/// �֐��� | AlgorithmGame
/// �ڍׁ@ | �A���S���Y���Q�[���̑S���s���e
/// </summary>
/// <param name="AlgoSlcNum">�X�e�[�W�̔ԍ�</param>
void AlgorithmGame(AlgoSlcNum) {
    //�X�e�[�W�I���ɍ��킹���}�b�v�̓ǂݍ���
    char MapFile[25];
    snprintf(MapFile, 25, "data/AlgoMap/map_%d.txt", AlgoSlcNum);
    AlgoMapLoad(MapFile);

    //�}�b�v�\��
    AlgoMapDisplay();

    //�L�[�����
    AlgoKeyGet();

    //���͂�����ꍇ�A���s
    if (GetKeyCount != 0) {
        //���s
        AlgoExecution();

        //���ʔ���
        AlgoJudge();
    }
}