#include "Key.h"
#include "data.h"
#include "DxLib.h"

double timer;

//ƒƒCƒ“ƒQ[ƒ€n‚Ü‚é‚Æ‚«‚É‚·‚é‰Šú‰»
void MainGameInit() {
	PlayerInit();
	EnemyInit();
	ShotInit();
	BackgroundInit();
	timer = 0;
}

void MainGameUpdate() {
	PlayerUpdate();
	EnemyUpdate();
	ShotUpdate();
	BackgroundUpdate();
	timer += 1.0 / mFps;
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
