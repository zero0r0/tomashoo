#include "Key.h"
#include "DxLib.h"
#include "data.h"


//�^�C�g�����ɏ��������鏈��������
void TitleInit() {

}

//�^�C�g�����ɍX�V���鏈��������
void TitleUpdata() {
	if (key_z > 0) {
		mode = MAIN;
		MainGameInit();
	}

}

//�^�C�g���ł̕`�揈��
void TitleDraw() {
	DrawString(0, 0, "�Ƃ܂���[�[�[�[�[�[�[�[�[!!", GetColor(255, 255, 255));
}