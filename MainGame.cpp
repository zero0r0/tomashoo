#include "Key.h"
#include "data.h"
#include "DxLib.h"

double timer = 0;

//ÉÅÉCÉìÉQÅ[ÉÄénÇ‹ÇÈÇ∆Ç´Ç…Ç∑ÇÈèâä˙âª
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
			//DrawCircle(shot[i].x + 24, shot[i].y + 24, shot[i].r, GetColor(255, 255, 255), true);
		}
	}
	DrawGraph(440,-5,weather_graphic[0],true);
	DrawFormatString(400,400, GetColor(255, 255, 255),"enemy : %d %d", enemy[1].x, enemy[1].y);
	//DrawFormatString(400, 420, GetColor(255, 255, 255), "stage : %lf", now_stage);
}
