#include "DxLib.h"
#include "Key.h"
#include "data.h"


void ItemInit() {

	for (int i = 0; i < 5; i++) {
		item[i].x = -10;
		item[i].y = -10;
		item[i].x_size = 48;
		item[i].y_size = 48;
		item[i].r = 17;
	}

}


void SpawnItem(int n) {
	if (n == 0) {
		for (int i = 0; i < MAX_ITEM / 2; i++) {
			item[i].x = GetRand(640);
			item[i].y = GetRand(-960);
		}
	}
	else {
		for (int i = MAX_ITEM/2; i < MAX_ITEM; i++) {
			item[i].x = GetRand(640);
			item[i].y = GetRand(-960);
		}
	}
}

void ItemUpdate() {
	for (int i = 0; i<5; i++) {
		item[i].y += player.speed;
		item[i].count++;
		if (item[i].count > 10) {
			item[i].state++;
		}
	}
}

void ItemDraw() {
	for (int i = 0; i<5; i++) {
		DrawGraph(item[i].x, item[i].y, tomato_item_graphic[item[i].state%2], true);
		//DrawCircle(item[i].x + 24, item[i].y + 24, item[i].r, GetColor(255, 255, 255), true);
	}
}
