#include "data.h"
#include "DxLib.h"
#include <math.h>

int stage = 0;


void BackgroundInit() {
	background[0].x = 0;
	background[0].y = -480;
	stage = 0;
}

void BackgroundUpdate() {
	if (background[stage].y >= 960) {
		background[stage].y -= 960;
		background[stage].loopNum++;
	}
	else {
		background[stage].y += player.speed;
	}
}

void BackgroundDraw() {
	DrawGraph(background[stage].x, background[stage].y, background[stage].graphic, true);
	DrawGraph(background[stage].x, background[stage].y - 960, background[stage].graphic, true);
}
