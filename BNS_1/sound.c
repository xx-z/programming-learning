#include <stdio.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")   // MSVC —p

void SoundNone() {
	PlaySound(TEXT("data/sound/none.wav"), NULL, SND_ASYNC);
}

void SoundClear() {
	PlaySound(TEXT("data/sound/clear.wav"), NULL, SND_ASYNC);
}

void SoundFailure() {
	PlaySound(TEXT("data/sound/failure.wav"), NULL, SND_ASYNC);
}

void SoundBotton() {
	PlaySound(TEXT("data/sound/botton.wav"), NULL, SND_ASYNC);
}

void SoundType() {
	PlaySound(TEXT("data/sound/type.wav"), NULL, SND_ASYNC);
}

void SoundTypeCancel() {
	PlaySound(TEXT("data/sound/type_cancel.wav"), NULL, SND_ASYNC);
}