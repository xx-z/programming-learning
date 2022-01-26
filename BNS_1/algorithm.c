/*****************************************************************************************************
*
*�@�A���S���Y���Q�[��
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>

#define  T_WHITE 0x0f
#define  T_RED 0x0c

#define MAXKEY 30                                       //�ő�L�[���͉�
#define MAXMAP 20                                      //�ő�}�b�v�T�C�Y

int KeyList[MAXKEY] = { 0 };                          //�L�[���͔z��
int GetKeyCount = 0;                                      //�L�[���͉�

char MapList[MAXMAP][MAXMAP];               //�}�b�v�̍s�񃊃X�g
int MapSizeX = 0, MapSizeY = 0;                   //�}�b�v��XY�̍ő�T�C�Y

int PlayerPosX = 0, PlayerPosY = 0;              //���݂̃v���[���[�̍��W

int ClearCount = 0;                                         //�N���A�J�E���g


/*****************************************************************************************************
* �֐��� | MapLoad
* �T�v�@ | �}�b�v�̓ǂݍ���
* �����@ | MapFile : �}�b�v�t�@�C���̖��O
* �߂�l | �Ȃ�
* �ڍׁ@ | �}�b�v�t�@�C���̃}�b�v��ǂݍ��݁AMapList�i�}�b�v�s��j�ɑ���A�}�b�v�̍ő�T�C�Y����
*****************************************************************************************************/
void MapLoad(MapFile) {
    const char* file = MapFile;
    FILE* fp;
    char c;
    int X = 0, Y = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("�t�@�C���G���[\n%s�̃I�[�v���Ɏ��s���܂����B\n", file);
        exit(1);
    }
    //EOF�܂Ńt�@�C�����當����1�������ǂݍ���
    while ((c = fgetc(fp)) != EOF) {
        //�񎟌��z���MapList�ɑ��
        if ('\n' == c) {
            if (MapSizeX < X) MapSizeX = X;
            Y++; X = 0;
        }
        else {
            if ('0' == c) ClearCount++;
            MapList[X][Y] = c; X++;
        }
    }
    MapSizeY = Y + 1;
    fclose(fp);
}


/*****************************************************************************************************
* �֐��� | MapDisplay
* �T�v�@ | �}�b�v�̕\��
* �����@ | �Ȃ�
* �߂�l | �Ȃ�
* �ڍׁ@ | MapList�i�}�b�v�s��j�̕\��
* �@�@�@ | 0 : �ʂ��Ă��Ȃ��ꏊ�@1: �ʂ����ꏊ�@2 : �v���[���[�@3 : ��
*****************************************************************************************************/
void MapDisplay() {
    HANDLE hStdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("\n");
    //�}�b�v�̃T�C�Y���\��
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if ('0' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
                printf("��");
            }
            else if ('1' == MapList[j][i]) {
                SetConsoleTextAttribute(hStdoutHandle, T_RED);
                printf("��");
            }
            else if ('2' == MapList[j][i]) {
                PlayerPosX = j; PlayerPosY = i;
                MapList[j][i] = '1';
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                printf("�@");
            }
            else {
                SetConsoleTextAttribute(hStdoutHandle, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                printf("�@");
            }
        }
        SetConsoleTextAttribute(hStdoutHandle, T_WHITE);
        printf("\n");
    }
    printf("\n����������������������������������������������������\n\n");
}


/*****************************************************************************************************
* �֐��� | KeyGet
* �T�v�@ | ���̓L�[
* �����@ | �Ȃ�
* �߂�l | �Ȃ�
* �ڍׁ@ | ���̓L�[��KeyList�ɑ��
*****************************************************************************************************/
void KeyGet() {
    int Key = 0;                                         //�L�[�̎��
    int Count = 0;                                      //���͉�

    //���͂����L�[��KeyList�ɑ��
    while (GetKeyCount != MAXKEY) {
        switch (getch()) {
        case 0xe0:
            switch (getch()) {
            case 0x48: Key = 1; printf("��"); break;
            case 0x4d: Key = 2; printf("��"); break;
            case 0x50: Key = 3; printf("��"); break;
            case 0x4b: Key = 4; printf("��"); break;
            }
            KeyList[GetKeyCount] = Key;
            GetKeyCount++; Count++;
            break;
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


/*****************************************************************************************************
* �֐��� | KeyDisplay
* �T�v�@ | ���̓L�[�̕\���A�����\��
* �����@ | KeyNumber�i�L�[���͔z��̑I�����ꂽ�l�j
* �߂�l | �Ȃ�
* �ڍׁ@ | KeyList�i���̓L�[�j�̕\���A���s���̖��L�[�̋����\��
*****************************************************************************************************/
void KeyDisplay(KeyNumber) {
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


/*****************************************************************************************************
* �֐��� | Execution
* �T�v�@ | ���̓L�[�����s
* �����@ | �Ȃ�
* �߂�l | �Ȃ�
* �ڍׁ@ | �L�[���͂ɉ����ăv���C���[���ړ������ĕ\��������
*****************************************************************************************************/
void Execution() {
    for (int i = 0; i < GetKeyCount; i++) {
        while (MapList[PlayerPosX][PlayerPosY] != '3') {
            //���̓L�[�ɍ��킹�ĂP�ړ�
            switch (KeyList[i]) {
            case 1: PlayerPosY--; break;
            case 2: PlayerPosX++; break;
            case 3: PlayerPosY++; break;
            case 4: PlayerPosX--; break;
            }
            //�ǂɓ������Ă��Ȃ��Ƃ�
            if (MapList[PlayerPosX][PlayerPosY] != '3') {
                if (MapList[PlayerPosX][PlayerPosY] == '0') ClearCount--;
                MapList[PlayerPosX][PlayerPosY] = '2';
                setCursorPos(0, 0);
                MapDisplay();
            }
            //�ǂɓ���������
            else {
                setCursorPos(0, MapSizeY + 4);
            }
            KeyDisplay(i);
            Sleep(700);
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


/*****************************************************************************************************
* �֐��� | Judgement
* �T�v�@ | �N���A����
* �����@ | �Ȃ�
* �߂�l | �Ȃ�
* �ڍׁ@ | ClearCount��0�̎��ɃN���A
*****************************************************************************************************/
void Judgement() {
    if (ClearCount == 0) printf("\n\nGame Clear!");
    else printf("\n\nFailure");
}


/*****************************************************************************************************
* �֐��� | AlgorithmGame
* �T�v�@ | �A���S���Y���Q�[����main�֐�
* �����@ | AlgoSlcNum�i�X�e�[�W�̔ԍ��j
* �߂�l | �Ȃ�
* �ڍׁ@ | �A���S���Y���Q�[���̑S���s���e
*****************************************************************************************************/
void AlgorithmGame(AlgoSlcNum) {
    //�X�e�[�W�I���ɍ��킹���}�b�v�̓ǂݍ���
    char MapFile[10];
    snprintf(MapFile, 10, "map_%d.txt", AlgoSlcNum);
    MapLoad(MapFile);

    //�}�b�v�\��
    MapDisplay();

    //�L�[�����
    KeyGet();

    //���s
    Execution();

    //���ʔ���
    Judgement();
}