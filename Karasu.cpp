#include "DxLib.h"
#include "data.h"
#include "Key.h"

//�v���C���[�̏������̊֐�
//�ʒu�A�����g�}�g�Ȃǂ�����������
void EnemyInit() {
	for (int i = 0; i < MAX_KARASU; i++) {
		karasu[i].x = 320;
		karasu[i].y = -10;
		karasu[i].x_size = 48;
		karasu[i].y_size = 48;
		karasu[i].is_dead = false;	//��ʁ����̓g�}�g�����������玀�񂾂Ƃ݂Ȃ�
	}
}

void EnemyUpdate() {
	for (int i = 0; i < MAX_KARASU; i++) {
		if (!karasu[i].is_dead) {
			karasu[i].y += player.speed;
		}
	}
}

void EnemyDraw() {
	for (int i = 0; i < MAX_KARASU; i++) {
		if (!karasu[0].is_dead) {
			DrawGraph(karasu[0].x, karasu[0].y, karasu[0].graphic[0], TRUE);
		}
	}
}
