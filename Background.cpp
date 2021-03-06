#include "data.h"
#include "DxLib.h"
#include <math.h>

int now_wave = 0;
bool last_stage = false;

void BackgroundInit() {
	last_stage = false;
	background[0].x = 0;
	background[0].y = -480;
	background[0].now_stage = 0;
	background[0].loopNum = 0;
	background[0].y_size = 960;

	background[1].x = 0;
	background[1].y = background[0].y - 960;
	background[1].now_stage = 0;
	background[1].loopNum = 0;
	background[1].y_size = 960;

	now_wave = 0;
	last_stage = false;
}

void BackgroundUpdate() {
	for (int i = 0; i < 2; i++) {
		//背景が下までスクロールしたら
		if (background[i].y >= 480) {
			//背景を変えるときの処理(背景が一定回数ループしたら)
			if (background[i].loopNum >= CHANGE_BACKGROUND_BY_LOOP_NUM
				&& background[i].now_stage < MAX_STAGE - 1) {
				//ループ回数リセットして背景を更新
				background[i].loopNum = 0;
				background[i].now_stage++;
				now_wave = (i == 1) ? background[i].now_stage : now_wave;
				//最終ステージだった場合
				if(background[i].now_stage == MAX_STAGE - 1) {
					background[i].y_size = 1920;
					now_wave = background[i].now_stage;
					if (i == 1)
						last_stage = true;
				}else {
					background[i].y_size = 960;
				}
			}
			//背景に変化がない場合
			else {
				//背景が畑の場合はアイテムを出す。
				if (background[i].now_stage == 1)
					SpawnItem(i);
				background[i].loopNum++;

				//敵を配置
				/*int enemy_num_count = 0;
				for (int j = 0; j < MAX_ENEMY; j++) {
					if (enemy[j].is_dead) {
						SpawnEnemy(j, background[i].now_stage, enemy_num_count);
						enemy_num_count++;
						if (ENEMY_SPAWN_NUM <= enemy_num_count)
							break;
					}
				}*/
			}
			background[i].y -= (background[i].y_size + background[(i+1)%2].y_size);
		}
	}
	for (int i = 0; i < 2; i++) {
		//ゴール付近で背景ストップ
		if (background[0].now_stage == MAX_STAGE - 1 && background[0].y > -200) {
			is_clear = true;//background[i].y = 0;
			player.speed = 0;
		}
		else
			background[i].y += player.speed;
	}
}

//描画
void BackgroundDraw() {
	DrawGraph(background[0].x, background[0].y, background_graphic[background[0].now_stage], true);
	if(!last_stage)
		DrawGraph(background[1].x, background[1].y, background_graphic[background[1].now_stage], true);
}