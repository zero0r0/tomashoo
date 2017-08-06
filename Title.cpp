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

typedef struct {
	int x, y;			
	int anim_state;		//アニメーション状態
	int anim_count;		//アニメーションのフレームカウント
	int page;			//ページ番号
	int page_flick_state;	
}Window;

UI title_tomato_label;
UI conveyor[3];
UI title_botton[3];
Window window;

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

	window.anim_count = 0;
	window.anim_state = 0;
	window.page = 0;
	window.x = 640 - 160;
	window.y = 0;
	window.page_flick_state = 0;

	title_state = 0;
	button_select_num = 0;
	bright = 0;
	alph = 0;
}

//タイトル時に更新する処理を書く
void TitleUpdata() {
	int anim_speed = 5;

	switch (title_state%6){
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
		case 2:
			if (WindowOpen()) {
				title_state++;
			}
			break;
		//ボタンを選択してる時の状態
		case 3:
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

			if (window.page_flick_state%3 == 0) {
				if (key_up == 1) {
					window.page_flick_state++;
					window.page = (window.page - 1 >= 0) ? window.page - 1 : 2;
				}
				else if (key_down == 1) {
					window.page_flick_state++;
					window.page++;
				}
			}
			else if (window.page_flick_state % 3 == 1) {
				if (WindowClose())
					window.page_flick_state++;
			}
			else {
				if (WindowOpen()) 
					window.page_flick_state++;
			}
			break;
		//ボタン（トマト）を流す
		case 4:
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
		case 5:
			TitleExit();
			break;
		default:
			break;
	}
}

//説明のウィンドウを開く関数 戻り値：全部開き終わったかどうか
bool WindowOpen() {
	if (0 <= window.anim_state && window.anim_state < 5) {
		window.anim_count++;
		if (window.anim_count % 5 == 0) {
			window.anim_state++;
		}
	}
	return (window.anim_state == 5);
}

//説明のウィンドウを閉じる関数 戻り値：全部閉じ終わったかどうか
bool WindowClose() {
	if (0 < window.anim_state && window.anim_state <= 5) {
		window.anim_count++;
		if (window.anim_count % 5 == 0) {
			window.anim_state--;
		}
	}
	return (window.anim_state == 0);
}

void TitleExit() {
	switch (button_select_num%3)
	{
		case 0:
			MainGameInit();
			scene = MAIN;
			break;
		case 1:
			RecordInit();
			scene = RECORD;
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
	DrawGraph(window.x, window.y,title_description_window_graphic[window.anim_state%6],true);
	if (window.anim_state == 5 && window.page_flick_state%3 == 0) {
		DrawGraph(window.x + 20, window.y + 10, title_desctiption_graphic[window.page%3], true);

		switch (window.page%3)
		{
			case 0:
				DrawStringToHandle(window.x + 42,145,"操作方法", GetColor(255, 255, 255),font_handle[0]);
				DrawStringToHandle(window.x + 5, 180, "←・→… 移動", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 200, "　↑　… 加速", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 220, "　↓　… 減速", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 240, "　ｚ　… トマシュ-!", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 260, "(Esc　… 終了)", GetColor(255, 255, 255), font_handle[0]);
				break;
			case 1:
				DrawStringToHandle(window.x + 25, 145, "ゲームについて", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 180,  "トマトを狙う敵にぶつかると", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 200,  "トマトの残数が減少します。", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 220,  "畑に実ってるトマトを拾って", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 240,  "たくさんトマトを運びましょう", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 260,  "中にはぶつかると減速したり、", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 280,  "トマトを全て持ってく敵も…?", GetColor(255, 255, 255), font_handle[1]);
				break;
			case 2:
				DrawStringToHandle(window.x + 35, 145, "クリアへの道", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 180, "制限時間までに指定数の", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 5, 200, "トマトをファミレスまで", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 5, 220, "届けられればクリア！！", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 5, 240, "邪魔する奴には・・・", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 35, 280, "トマシュー！", GetColor(255, 255, 255), font_handle[0]);
				break;
			default:
				break;
		}

	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alph);		//ブレンドモードをα(128/255)に設定
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);  //画面全体に白い四角形を描画
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	//DrawFormatString(100, 100, GetColor(255, 255, 255), "%d %d %d", conveyor[0].x, conveyor[1].x, conveyor[2].x);
}