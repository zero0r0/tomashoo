#include "Key.h"
#include "DxLib.h"
#include "data.h"

int logo_x[3];
int logo_y[3];
int title_state;
int button_select_num;
int bright;
int alph;

typedef struct {
	int x, y;
	int state;
}UI;

UI title_tomato_label;
UI conveyor[3];
UI title_botton[3];

//タイトル時に初期化する処理を書く
void TitleInit() {
	logo_y[0] = 43;
	logo_y[1] = 43;
	logo_y[2] = 172;

	logo_x[0] = 110;
	logo_x[1] = 210;
	logo_x[2] = 260;

	title_tomato_label.x = 700;
	title_tomato_label.y = 90;
	title_tomato_label.state = 0;

	for (int i = 0; i < 3; i++) {
		conveyor[i].x = -1 * 640 * i;
		conveyor[i].y = 480 - 170;
		title_botton[i].x = -640 + 150 * (i + 1);
		title_botton[i].y = 350;
		title_botton[i].state = 0;
	}

	title_state = 0;
	button_select_num = 0;
	bright = 0;
	alph = 0;
}

//タイトル時に更新する処理を書く
void TitleUpdata() {
	int anim_speed = 5;

	switch (title_state%5){
		//画面を明るくして、タイトルロゴをそろえる状態
		case 0:
			if (0 <= bright  && bright < 255) {
				bright = (255 < bright + anim_speed) ? 255 : bright + anim_speed;
			}else if (title_tomato_label.x > 330) {
				title_tomato_label.x -= anim_speed;
				if (CheckHitKeyAll() != 0)
					title_tomato_label.x = 330;
			}else {
				title_tomato_label.state++;
				title_state++;
				PlaySoundMem(tubure_se, DX_PLAYTYPE_BACK, true);
				PlaySoundMem(title_bgm, DX_PLAYTYPE_LOOP, true);
			}
			break;
		//コンベア、ボタンをそろえる状態
		case 1:
			if (conveyor[1].x < 0) {
				for (int i = 0; i < 3; i++) {
					conveyor[i].x += anim_speed;
					title_botton[i].x += anim_speed;
				}
				if (CheckHitKeyAll() != 0) {
					for (int i = 0; i < 3; i++) {
						title_botton[i].x = 150 * (i + 1);
						conveyor[i].x = 640 - (1 * 640 * i);
					}
				}
			}
			else {
				title_state++;
			}
			break;
		//ボタンを選択してる時の状態
		case 2:
			for (int i = 0; i < 3; i++) {
				title_botton[i].y = (i == button_select_num % 3) ? 350 - 20 : 350;
			}
			if (key_right == 1)
				button_select_num++;
			else if (key_left == 1)
				button_select_num--;
			else if (key_z == 1) {
				for (int i = 0; i < 3; i++) {
					title_botton[i].y = 350;
					title_botton[i].state = (i == button_select_num % 3) ? 0 : 1;
				}
				title_state++;
				PlaySoundMem(tubure_se, DX_PLAYTYPE_BACK, true);
				StopSoundMem(title_bgm);
			}
			break;
		//ボタン（トマト）を流す
		case 3:
			if (conveyor[2].x <= -10) {
				for (int i = 0; i < 3; i++) {
					conveyor[i].x += anim_speed;
					title_botton[i].x += anim_speed;
				}
			}else if (0 <= alph  && alph < 255) {
				alph = (255 < alph + anim_speed) ? 0 : anim_speed + alph;
			}
			else {
				title_state++;
			}
			break;
		//指定した処理を最後に行う
		case 4:
			TitleExit();
			break;
		default:
			break;
	}
}

void TitleExit() {
	switch (button_select_num%3)
	{
		case 0:
			MainGameInit();
			scene = MAIN;
			break;
		case 1:
			break;
		case 2:
			is_exit = true;
			break;
		default:
			break;
	}
}

//タイトルでの描画処理
void TitleDraw() {
	SetDrawBright(bright, bright, bright);
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);  //画面全体に白い四角形を描画

	for (int i = 0; i < 3; i++) {
		DrawGraph(logo_x[i], logo_y[i],titlelogo_graphic[i],true);
		DrawGraph(conveyor[i].x, conveyor[i].y, title_conbea_graphic, true);
	}
	for (int i = 0; i < 3; i++) {
		if (title_botton[i].state % 2 == 0) {
			DrawGraph(title_botton[i].x, title_botton[i].y, title_botton_graphic[i], true);
		}
		else {
			DrawGraph(title_botton[i].x, title_botton[i].y, title_pushed_tomato_graphic, true);
		}
	}
	DrawGraph(title_tomato_label.x, title_tomato_label.y, title_tomato_graphic[title_tomato_label.state % 2], true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alph);		//ブレンドモードをα(128/255)に設定
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);  //画面全体に白い四角形を描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d %d %d", conveyor[0].x, conveyor[1].x, conveyor[2].x);
}