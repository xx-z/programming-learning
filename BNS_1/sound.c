/*****************************************************************************************************
*
*�@���ʉ��̃T�E���h�֐�
*
*****************************************************************************************************/

#include <stdio.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")   // MSVC �p

//������
void SoundNone() {
	PlaySound(TEXT("data/sound/none.wav"), NULL, SND_ASYNC);
}

//�Q�[���N���A
void SoundClear() {
	PlaySound(TEXT("data/sound/clear.wav"), NULL, SND_ASYNC);
}

//�Q�[�����s
void SoundFailure() {
	PlaySound(TEXT("data/sound/failure.wav"), NULL, SND_ASYNC);
}

//�{�^����I��
void SoundBotton() {
	PlaySound(TEXT("data/sound/botton.wav"), NULL, SND_ASYNC);
}

//���͂Ȃǂ̃^�C�v��
void SoundType() {
	PlaySound(TEXT("data/sound/type.wav"), NULL, SND_ASYNC);
}

//�������A�߂�Ȃǂ̃^�C�v��
void SoundTypeCancel() {
	PlaySound(TEXT("data/sound/type_cancel.wav"), NULL, SND_ASYNC);
}