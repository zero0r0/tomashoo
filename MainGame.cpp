#include "Key.h"
#include "data.h"
#include "DxLib.h"

double timer = 0;
int total_distance = 0;

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
	PlaySoundMem(stage_bgm[0], DX_PLAYTYPE_BACK,true);
}

void MainGameUpdate() {
	//27日エッグ変更
	if (!is_clear) {
		total_distance += player.speed;
		length = (int)((18513 - total_distance) * (1.0 / 185));
		if (length < 0)
			length = 0;
	}else if(player.tomato < 50){
		GameoverInit(1);
		return;
	}else if (player.time <= 0) {
		GameoverInit(2);
		return;
	}else if (is_clear) {
		GameClearInit();
		return;
	}

	//前奏が再生中終了して、ループが再生されてない場合ループ再生開始
	if (CheckSoundMem(stage_bgm[0]) == 0 && CheckSoundMem(stage_bgm[1]) == 0) {
		PlaySoundMem(stage_bgm[1], DX_PLAYTYPE_LOOP,true);
	}
	PlayerUpdate();
	EnemyUpdate();
	ShotUpdate();
	BackgroundUpdate();
	ItemUpdate();
	//timer += (1.0) * mFps;
}

void MainGameDraw() {
	BackgroundDraw();
	ItemDraw();
	PlayerDraw();
	EnemyDraw();
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].is_active) {
			DrawGraph(shot[i].x, shot[i].y, shot_graphic, true);
			//DrawCircle(shot[i].x + 24, shot[i].y + 24, sh[]ot[i].r, GetColor(255, 255, 255), true);
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
