#include "data.h"
#include "DxLib.h"
#include <math.h>


void BackgroundInit() {
	background[0].x = 0;
	background[0].y = -480;
	background[0].now_stage = 0;
	background[0].loopNum = 0;

	background[1].x = 0;
	background[1].y = background[0].y - 960;
	background[1].now_stage = 0;
	background[1].loopNum = 0;
}

void BackgroundUpdate() {
	for (int i = 0; i < 2; i++) {
		if (background[i].y >= 480) {
			background[i].y -= 480 + 960 - player.speed;
			if(background[i].now_stage==1) SpawnItem(i);
			background[i].loopNum++;
			if (background[i].loopNum >= CHANGE_BACKGROUND_BY_LOOP_NUM 
				&& background[i].now_stage < MAX_STAGE-1 ) {
				background[i].loopNum = 0;
				background[i].now_stage++;
			}
		}else {
			background[i].y += player.speed;
		}
	}
}

void BackgroundDraw() {
	DrawGraph(background[0].x, background[0].y, background_graphic[background[0].now_stage], true);
	DrawGraph(background[1].x, background[1].y, background_graphic[background[1].now_stage], true);
}