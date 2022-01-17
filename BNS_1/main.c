#include <stdio.h>

int MaxKey = 5;
int KeyArr[30] = { 0 };         //‘S‚Ä‚ÌƒL[“ü—Í
int GetKeyCount = 0;                  //

void MapLoad() {

}

void KeyAdd(Key) {
    KeyArr[GetKeyCount] = Key;
}

void KeyGet() {
    int Key = 0;
    for (GetKeyCount = 0; GetKeyCount < MaxKey; GetKeyCount++) {
        switch (getch()) {
            case 0xe0:
                switch (getch()) {
                    case 0x48: Key = 1; printf("ª"); break;
                    case 0x4d: Key = 2; printf("¨"); break;
                    case 0x50: Key = 3; printf("«"); break;
                    case 0x4b: Key = 4; printf("©"); break;
                }
                KeyAdd(Key);
                break;
            case 0x0d: 
                printf("enter"); 
                GetKeyCount = MaxKey;
                break;
        }
    }
}

void main() {
    MapLoad();
    KeyGet();
    printf("\n////////////////////////////\n");
    for (int i = 0; i < 30; i++) {
        printf("%d", KeyArr[i]);
    }
}

/*
printf("\x1b[41m    ¡¡¡¡\x1b[m\n"); 
printf("\x1b[34m    ¡¡¡¡\033[m\n");
*/