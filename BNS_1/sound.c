/*****************************************************************************************************
*
*　効果音のサウンド関数
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")   // MSVC 用

//音無し
void SoundNone() {
	PlaySound(TEXT("data/sound/none.wav"), NULL, SND_ASYNC);
}

//ゲームクリア
void SoundClear() {
	PlaySound(TEXT("data/sound/clear.wav"), NULL, SND_ASYNC);
}

//ゲーム失敗
void SoundFailure() {
	PlaySound(TEXT("data/sound/failure.wav"), NULL, SND_ASYNC);
}

//ボタンを選択
void SoundBotton() {
	PlaySound(TEXT("data/sound/botton.wav"), NULL, SND_ASYNC);
}

//入力などのタイプ音
void SoundType() {
	PlaySound(TEXT("data/sound/type.wav"), NULL, SND_ASYNC);
}

//取り消し、戻るなどのタイプ音
void SoundTypeCancel() {
	PlaySound(TEXT("data/sound/type_cancel.wav"), NULL, SND_ASYNC);
}