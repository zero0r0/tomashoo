#include "Key.h"
#include "DxLib.h"
#include "data.h"


//�^�C�g�����ɏ��������鏈��������
void TitleInit() {

}

//�^�C�g�����ɍX�V���鏈��������
void TitleUpdata() {
	if (key_z == 1) {
		MainGameInit();
		scene = MAIN;
	}

}

//�^�C�g���ł̕`�揈��
void TitleDraw() {
	DrawString(0, 0, "�Ƃ܂���[�[�[�[�[�[�[�[�[!!", GetColor(255, 255, 255));
	DrawString(100, 100, "push Z key", GetColor(255, 255, 255));
	//DrawGraph(0, 0, background_graphic[MAX_STAGE-1], true);
}