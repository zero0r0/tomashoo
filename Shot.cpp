#include "DxLib.h"
#include "data.h"
#include "Key.h"

//弾が当たったときのエフェクト
Effect tomato_effect[MAX_TOMATO];

void ShotInit() {
	for (int i = 0; i < MAX_TOMATO; i++) {
		shot[i].x = -100;
		shot[i].y = -100;
		shot[i].x_size = 48;
		shot[i].y_size = 48;
		shot[i].r = 20;
		shot[i].is_active = false;

		tomato_effect[i].x = -10;
		tomato_effect[i].y = -10;
		tomato_effect[i].count = 0;
		tomato_effect[i].is_used = false;
		tomato_effect[i].state = 0;
	}

}

void ShotUpdate() {
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].is_active) {
			shot[i].y -= 10;
			if (shot[i].y < 0 - shot[i].y_size)
				shot[i].is_active = false;
		}
	}

	for (int i = 0; i < MAX_TOMATO; i++){
		if (tomato_effect[i].is_used) {
			tomato_effect[i].y += player.speed;

			if (tomato_effect[i].count > 15 && tomato_effect[i].state == 0) {
				tomato_effect[i].state++;
				tomato_effect[i].count = 0;
			}
			else
				tomato_effect[i].count++;

			//エフェクト画面外判定
			if (tomato_effect[i].y >= 500) {
				tomato_effect[i].count = 0;
				tomato_effect[i].x = -10;
				tomato_effect[i].y = -10;
				tomato_effect[i].state = 0;
				tomato_effect[i].is_used = false;
			}
		}
	}
	
	for (int j = 0; j < MAX_TOMATO; j++) {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (shot[j].is_active && !enemy[i].is_dead && ((shot[j].x + shot[j].x_size / 2) - (enemy[i].x + enemy[i].x_size / 2)) * ((shot[j].x + shot[j].x_size / 2) - (enemy[i].x + enemy[i].x_size / 2)) + (shot[j].y + shot[j].y_size / 2 - (enemy[i].y + enemy[i].y_size / 2)) * ((shot[j].y + shot[j].y_size / 2) - (enemy[i].y + enemy[i].y_size / 2)) <= (shot[j].r + enemy[i].r) * (shot[j].r + enemy[i].r)) { //２２日エッグ変更
				if(enemy[i].type < 7)
					enemy[i].is_dead = true;
				//shot[j].life = 0;
				PlaySoundMem(tubure_se, DX_PLAYTYPE_BACK, true);
				shot[j].is_active = false;
				for (int k = 0; k < MAX_TOMATO; k++) {
					if (!tomato_effect[k].is_used) {
						tomato_effect[k].x = enemy[i].x;
						tomato_effect[k].y = enemy[i].y;
						tomato_effect[k].is_used = true;
						break;
					}
				}
			}
		}
	}

}