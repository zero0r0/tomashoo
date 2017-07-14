#include "DxLib.h"
#include "data.h"
#include "Key.h"

void ShotInit() {
	for (int i = 0; i < MAX_TOMATO; i++) {
		shot[i].x = -100;
		shot[i].y = -100;
		shot[i].x_size = 48;
		shot[i].y_size = 48;
	}
}

void ShotUpdate() {
	for (int i = 0; i < MAX_TOMATO; i++) {
		if (shot[i].life > 0) {
			shot[i].y -= 10;
			if (shot[i].y < 0 - shot[i].y_size)
				shot[i].life = 0;
		}
	}
	
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].x <= shot[i].x + shot[i].x_size && enemy[i].x + enemy[i].x_size >= shot[i].x) {
			if (enemy[i].y <= shot[i].y + shot[i].y_size && enemy[i].y + enemy[i].y_size >= shot[i].y) {
				enemy[i].is_dead = true;
			}
		}
	}
}