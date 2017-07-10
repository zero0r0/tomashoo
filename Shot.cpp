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
	
	for (int i = 0; i < MAX_KARASU; i++) {
		if (karasu[i].x <= shot[i].x + shot[i].x_size && karasu[i].x + karasu[i].x_size >= shot[i].x) {
			if (karasu[i].y <= shot[i].y + shot[i].y_size && karasu[i].y + karasu[i].y_size >= shot[i].y) {
				karasu[i].is_dead = true;
			}
		}
	}
}