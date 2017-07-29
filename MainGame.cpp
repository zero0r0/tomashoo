#include "Key.h"
#include "data.h"
#include "DxLib.h"

double timer = 0;

//メインゲーム始まるときにする初期化
void MainGameInit() {
	PlayerInit();
	EnemyInit();
	ShotInit();
	BackgroundInit();
	ItemInit();
	total_distance = 0;
	timer = 0;
	is_clear = false;
	//25日エッグ変更
	weather_number = GetRand(2);
}

void MainGameUpdate() {
	PlayerUpdate();
	EnemyUpdate();
	ShotUpdate();
	BackgroundUpdate();
	ItemUpdate();
	//timer += (1.0) * mFps;
	//27日エッグ変更
	if (!is_clear) {
		total_distance += player.speed;//* (1.0 / mFps);
	}
	if (CheckHitKey(KEY_INPUT_RETURN) == 1 && is_clear) {
		scene = TITLE;
	}


}

void MainGameDraw() {
	BackgroundDraw();
	ItemDraw();
	PlayerDraw();
	EnemyDraw();
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].is_active) {
			DrawGraph(shot[i].x, shot[i].y, shot_graphic, true);
			//DrawCircle(shot[i].x + 24, shot[i].y + 24, shot[i].r, GetColor(255, 255, 255), true);
		}
		if (tomato_effect[i].is_used) {
			DrawGraph(tomato_effect[i].x, tomato_effect[i].y,tomato_effect_graphic[tomato_effect[i].state%2],true);
		}
	}
	//DrawGraph(440,-5,weather_graphic[0],true);

	//25日エッグ変更    
	DrawGraph(440, -5, weather_graphic[weather_number], true);
	if(is_clear)
		DrawFormatString(400,400, GetColor(255, 255, 255),"returnキーおして");
}
