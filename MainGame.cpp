#include "Key.h"
#include "data.h"
#include "DxLib.h"



//メインゲーム始まるときにする初期化
void MainGameInit() {
	PlayerInit();
	EnemyInit();
	ShotInit();
	BackgroundInit();
}

void MainGameUpdate() {
	PlayerUpdate();
	EnemyUpdate();
	ShotUpdate();
	BackgroundUpdate();
}

void MainGameDraw() {
	BackgroundDraw();
	PlayerDraw();
	EnemyDraw();
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].life > 0) {
			DrawGraph(shot[i].x, shot[i].y, tomato_graphic, true);
		}
	}
}
