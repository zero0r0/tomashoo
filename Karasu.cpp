#include "DxLib.h"
#include "data.h"
#include "Key.h"

//�v���C���[�̏������̊֐�
//�ʒu�A�����g�}�g�Ȃǂ�����������
void KarasuInit() {
	karasu[0].x = 100;
	karasu[0].y = 100;
	karasu[0].x_size = 48;
	karasu[0].y_size = 48;
}


void KarasuUpdate() {

}

void KarasuDraw() {
	DrawGraph(karasu[0].x, karasu[0].y, karasu[0].graphic[0], TRUE);
}
