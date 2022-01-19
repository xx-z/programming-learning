#include <stdio.h>
#include <stdlib.h>

#define MAXKEY 20                                //�ő�L�[���͉�
#define MAXMAP 20                             //�ő�}�b�v�T�C�Y

int KeyList[MAXKEY] = { 0 };                  //�L�[���̓��X�g
int GetKeyCount = 0;                             //�L�[���͉�

char MapList[MAXMAP][MAXMAP];
int MapSizeX, MapSizeY = 0;

int PlayerPosX, PlayerPosY = 0;

//�}�b�v�̓ǂݍ���
void MapLoad() {
    const char* file = "map_1.txt";
    FILE* fp;
    char c;
    int X = 0;
    int Y = 0;

    fopen_s(&fp, file, "r");
    if (fp == NULL) {
        printf("�t�@�C���G���[\n%s�̃I�[�v���Ɏ��s���܂����B\n", file);
        exit(1);
    }
    //	EOF�܂Ńt�@�C�����當����1�������ǂݍ���
    while ((c = fgetc(fp)) != EOF) {
        if ('\n' == c) {
            if (MapSizeX < X) {
                MapSizeX = X;
            }
            Y++; X = 0;
        }
        else {
            MapList[X][Y] = c;
            X++; 
        }
    }
    MapSizeY = Y + 1;
    fclose(fp);
}

//�}�b�v�̕\��
void MapDisplay() {
    //printf("%d, %d\n", MapSizeX, MapSizeY);
    printf("\n");
    //�{�}�b�v����
    //0:off   1:on   2:start   3:wall
    for (int i = 0; i < MapSizeY; i++) {
        for (int j = 0; j < MapSizeX; j++) {
            if ('0' == MapList[j][i]) {
                printf("��");
            } else if ('2' == MapList[j][i]){
                PlayerPosX = j; PlayerPosY = i;
                MapList[j][i] = '1';
                printf("\x1b[44m�@\x1b[m");
            } else {
                printf("\x1b[47m�@\x1b[m");
            }
        }
        printf("\n");
    }

}

//�L�[���X�g�ɃL�[��������֐�
void KeyAdd(Key) {
    KeyList[GetKeyCount] = Key;
}

//�L�[���͌��m
void KeyGet() {
    int Key = 0;
    for (GetKeyCount = 0; GetKeyCount < MAXKEY; GetKeyCount++) {
        switch (getch()) {
            case 0xe0:
                switch (getch()) {
                    case 0x48: Key = 1; printf("��"); break;
                    case 0x4d: Key = 2; printf("��"); break;
                    case 0x50: Key = 3; printf("��"); break;
                    case 0x4b: Key = 4; printf("��"); break;
                }
                KeyAdd(Key);
                break;
            case 0x0d: 
                printf("\n"); 
                GetKeyCount = MAXKEY;
                break;
        }
    }
}

void Execution() {
    //printf("%d%d", PlayerPosX, PlayerPosY);
    for (int i = 0; i < MAXKEY; i++) {
        while (MapList[PlayerPosX][PlayerPosY] != '3') {
            switch (KeyList[i]) {
                case 1: PlayerPosY--; break;
                case 2: PlayerPosX++; break;
                case 3: PlayerPosY++; break;
                case 4: PlayerPosX--; break;
            }
        } 
        if (MapList[PlayerPosX][PlayerPosY] == '3') {
            switch (KeyList[i]) {
                case 1: PlayerPosY++; break;
                case 2: PlayerPosX--; break;
                case 3: PlayerPosY--; break;
                case 4: PlayerPosX++; break;
            }
        }
        printf(", %d%d", PlayerPosX, PlayerPosY);
    }
}

void main() {
    MapLoad();
    MapDisplay();
    printf("\n����������������������������������������������������\n\n");
    KeyGet();
    Execution();
}

/*
printf("\x1b[41m�@\x1b[m\n"); 
printf("\x1b[34m����������������\033[m\n");
*/