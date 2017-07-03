#include "Key.h"
#include "data.h"
#include "DxLib.h"



//���C���Q�[���n�܂�Ƃ��ɂ��鏉����
void MainGameInit() {
	PlayerInit();
	KarasuInit();
	ShotInit();
}

void MainGameUpdate() {
	PlayerUpdate();
	KarasuUpdate();
	ShotUpdate();
}

void MainGameDraw() {
	PlayerDraw();
	KarasuDraw();
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].life > 0) {
			DrawGraph(shot[i].x, shot[i].y, tomato_graphic, true);
		}
	}
}
