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
	int anim_state;		//�A�j���[�V�������
	int anim_count;		//�A�j���[�V�����̃t���[���J�E���g
	int page;			//�y�[�W�ԍ�
	int page_flick_state;	
}Window;

UI title_tomato_label;
UI conveyor[3];
UI title_botton[3];
Window window;

//�^�C�g�����ɏ��������鏈��������
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

//�^�C�g�����ɍX�V���鏈��������
void TitleUpdata() {
	int anim_speed = 5;
	/*
	if (key_a > 0)
		x--;
	if (key_d > 0)
		x++;
	if (key_w > 0)
		y++;
	if (key_s > 0)
		y--;
	if (key_x > 0)
		scale++;
	*/

	switch (title_state%6){
		//��ʂ𖾂邭���āA�^�C�g�����S�����낦����
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
		//�R���x�A�A�{�^�������낦����
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
		//�{�^����I�����Ă鎞�̏��
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
		//�{�^���i�g�}�g�j�𗬂�
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
		//�w�肵���������Ō�ɍs��
		case 5:
			TitleExit();
			break;
		default:
			break;
	}
}

//�����̃E�B���h�E���J���֐� �߂�l�F�S���J���I��������ǂ���
bool WindowOpen() {
	if (0 <= window.anim_state && window.anim_state < 5) {
		window.anim_count++;
		if (window.anim_count % 5 == 0) {
			window.anim_state++;
		}
	}
	return (window.anim_state == 5);
}

//�����̃E�B���h�E�����֐� �߂�l�F�S�����I��������ǂ���
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

//�^�C�g���ł̕`�揈��
void TitleDraw() {
	SetDrawBright(bright, bright, bright);
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);  //��ʑS�̂ɔ����l�p�`��`��

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
		DrawGraph(window.x + 20, window.y + 12, title_desctiption_graphic[window.page%3], true);
		int x = 560, y1 = 310, y2 = 10;
		int scale = 10;
		DrawTriangle(x, y1 + scale, x - scale, y1, x + scale, y1, GetColor(255, 0, 0), TRUE);
		DrawTriangle(x, y2 - scale, x - scale, y2, x + scale, y2, GetColor(255, 0, 0), TRUE);
		switch (window.page%3)
		{
			case 0:
				DrawStringToHandle(window.x + 42,145,"������@", GetColor(255, 255, 255),font_handle[0]);
				DrawStringToHandle(window.x + 5, 180, "���E���c �ړ�", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 200, "�@���@�c ����", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 220, "�@���@�c ����", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 240, "�@���@�c �g�}�V��-!", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 260, "(Esc�@�c �I��)", GetColor(255, 255, 255), font_handle[0]);
				break;
			case 1:
				DrawStringToHandle(window.x + 25, 145, "�Q�[���ɂ���", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 180,  "�g�}�g��_���G�ɂԂ����", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 200,  "�g�}�g�̎c�����������܂��B", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 220,  "���Ɏ����Ă�g�}�g���E����", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 240,  "��������g�}�g���^�т܂��傤", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 260,  "���ɂ͂Ԃ���ƌ���������A", GetColor(255, 255, 255), font_handle[1]);
				DrawStringToHandle(window.x + 5, 280,  "�g�}�g��S�Ď����Ă��G���c?", GetColor(255, 255, 255), font_handle[1]);
				break;
			case 2:
				DrawStringToHandle(window.x + 35, 145, "�N���A�ւ̓�", GetColor(255, 255, 255), font_handle[0]);
				DrawStringToHandle(window.x + 5, 180, "�������Ԃ܂łɎw�萔��", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 5, 200, "�g�}�g���t�@�~���X�܂�", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 5, 220, "�͂�����΃N���A�I�I", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 5, 240, "�ז�����z�ɂ́E�E�E", GetColor(255, 255, 255), font_handle[2]);
				DrawStringToHandle(window.x + 35, 280, "�g�}�V���[�I", GetColor(255, 255, 255), font_handle[0]);
				break;
			default:
				break;
		}

	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alph);		//�u�����h���[�h����(128/255)�ɐݒ�
	DrawBox(0, 0, 640, 480, GetColor(255, 255, 255), TRUE);  //��ʑS�̂ɔ����l�p�`��`��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//�u�����h���[�h���I�t
	//DrawFormatString(100, 100, GetColor(0,0,0), "%d %d %d", x,y,scale);
}