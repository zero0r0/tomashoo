#include "Key.h"
#include "DxLib.h"
#include "data.h"
/*
int b_size_x = 130;
int b_size_y = 140;
int b_x = 330;
int b_y = 320;
*/
void RecordInit() {

}

void RecordUpdate() {
	if (key_z == 1) {
		TitleInit();
		scene = TITLE;
	}
	/*
	if (key_down > 1)
		b_y++;
	else if (key_up > 1)
		b_y--;
	else if (key_left > 1)
		b_x--;
	else if (key_right > 1)
		b_x++;
	else if (key_a > 1)
		b_size_x--;
	else if (key_d > 1)
		b_size_x++;
	else if (key_w > 1)
		b_size_y--;
	else if (key_s > 1)
		b_size_y++;
		*/
}


void RecordDraw() {
	
	int b_size_x = 330;
	int b_size_y = 220;
	int b_x = 130;
	int b_y = 140;
	
	//if (0 < max_score) {
	//	DrawGraph(0, 0, gameclear_graphic, true);
	//}
	//else {
	DrawGraph(0, 0, record_graphic, true);
	//}
	DrawBox(b_x, b_y, b_x + b_size_x, b_y + b_size_y, GetColor(255, 255, 255), true);

	DrawFormatStringToHandle(170, 180, GetColor(255, 0, 0), font_handle[3], "ハイスコア");
	DrawGraph(325, 250, font_num_graphic[max_score % 10], true);
	DrawGraph(290, 250, font_num_graphic[(max_score / 10) % 10], true);
	DrawGraph(255, 250, font_num_graphic[(max_score / 100) % 10], true);
	DrawGraph(220, 250, font_num_graphic[(max_score / 1000) % 10], true);

	//DrawFormatString(0,100,GetColor(255,0,0),"position(%d,%d)",b_x,b_y);
	//DrawFormatString(0, 200, GetColor(255, 0, 0), "scale(%d,%d)", b_size_x, b_size_y);
}