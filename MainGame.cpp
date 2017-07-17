#include "Key.h"
#include "data.h"
#include "DxLib.h"

double timer = 0;

//ƒƒCƒ“ƒQ[ƒ€n‚Ü‚é‚Æ‚«‚É‚·‚é‰Šú‰»
void MainGameInit() {
	PlayerInit();
	EnemyInit();
	ShotInit();
	BackgroundInit();
	ItemInit();
	total_distance = 0;
	timer = 0;
}

void MainGameUpdate() {
	PlayerUpdate();
	EnemyUpdate();
	ShotUpdate();
	BackgroundUpdate();
	ItemUpdate();
	timer += (1.0) * mFps;
}

void MainGameDraw() {
	BackgroundDraw();
	ItemDraw();
	PlayerDraw();
	EnemyDraw();
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].life > 0) {
			DrawGraph(shot[i].x, shot[i].y, shot_graphic, true);
		}
	}
	DrawGraph(440,-5,weather_graphic[0],true);
}
