#include "DxLib.h"
#include "Key.h"
#include "data.h"

#define WINDOW_XSIZE 640
#define WINDOW_YSIZE 480


void TestMessage();		//�֐��̃v���g�^�C�v�錾
void LoadGraphicAll();
void DeleteGraphicAll();


Player player;
Shot shot[MAX_TOMATO];
Item item[MAX_TOMATO];
Karasu karasu[MAX_KARASU];

int mode;
int const TITLE = 0;
int const MAIN = 1;
int const GAMEOVER = 2;

//�O���t�B�b�N�n
int shot_graphic;
int tomato_graphic;
int speed_meter_graphic;
int backbround_graphic[STAGE_NUM];

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hp, LPSTR lpC, int nC) {

	/*----------------����{�I�Ȑݒ�----------------------
	��{�I�Ȑݒ�͂ǂ̃Q�[���ł��قڃR�s�y�Ȃ̂ŁA
	�Ӗ��͂��܂�C�ɂ��Ȃ��Ă������[
	*/
	ChangeWindowMode(TRUE);					//�E�B���h�E���[�h�ɂ���
	SetMainWindowText("�e�X�g�Q�[��");		//�E�B���h�E�̃^�C�g����ύX����
	SetWindowSizeChangeEnableFlag(FALSE);
	SetGraphMode(WINDOW_XSIZE, WINDOW_YSIZE, 32);				//�E�B���h�E�̃T�C�Y��640x480�ɂ���
	SetWindowSizeExtendRate(1);

	if (DxLib_Init() == -1) return -1;		//Dx���C�u����������������
	SetOutApplicationLogValidFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);			//�`��Ώۂ𗠉�ʂɂ���

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);  //�t�H���g�̐ݒ�
	SetFontSize(18);

	/*----------------����{�I�Ȑݒ�----------------------*/

	//�w�i�̏�񂢂낢��
	int back_y;
	int back_g = LoadGraph("Data/back.bmp");

	//�Q�[���̏�񂢂낢��
	int score;
	int max_score = 0;

	FILE* rf;
	//�t�@�C����ǂݍ���
	fopen_s(&rf, "Data/max_score.txt", "r");
	//�t�@�C���̓ǂݍ��݂ɐ���������A��������l��ǂݍ���
	if (rf != NULL) {
		fread(&max_score, sizeof(int), 1, rf);
		fclose(rf);	//�t�@�C�������
	}
	
	LoadGraphicAll();

	mode = TITLE;
	TitleInit();

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		KeyUpdate();
		//--------------�Q�[���̏���������-----------------
		//�ϐ��umode�v��0�Ȃ�΁A�^�C�g����ʂ̏���������
		switch (mode) {
		case TITLE:
			TitleUpdata();
			TitleDraw();
			break;
		case MAIN:
			MainGameUpdate();
			MainGameDraw();
			break;
		case GAMEOVER:
			break;
		default:
			break;
		}
		/*
			

			//�g���K�[��-1����
			shot_trigger--;
			//Z�L�[��������Ă��āA���g���K�[��0�ȉ���������e�ۂ𔭎˂���
			if (key_z > 0 && shot_trigger <= 0) {
				//�g�p����Ă��Ȃ��e�ۂ�T���A������������Z�b�g���Ĕ����o��
				for (i = 0; i < MAX_SHOT; i++) {
					if (shot_life[i] == 0) {
						shot_life[i] = 1;
						shot_xsize[i] = 20;
						shot_ysize[i] = 20;
						shot_x[i] = player_x + player_xsize / 2 - shot_xsize[i] / 2;
						shot_y[i] = player_y;

						//�g���K�[��ݒ�
						shot_trigger = 10;
						break;		//���[�v����E�o
					}
				}
			}
			//�������g�p���āA1/20�̊m���œG���o��������
			//��1���[�v�ɂ�1/20�A60���[�v/1�b�̂��߁A���������G��1�b��3�̏o��v�Z�ƂȂ�
			if (GetRand(20) == 0) {
				//�g�p����Ă��Ȃ��G��T���A������������Z�b�g���Ĕ����o��
				for (i = 0; i < MAX_ENEMY; i++) {
					if (enemy_life[i] == 0) {
						enemy_life[i] = 1;
						enemy_xsize[i] = 40;
						enemy_ysize[i] = 40;
						enemy_x[i] = GetRand(440 - enemy_xsize[i]);
						enemy_y[i] = 0 - enemy_ysize[i];

						break;
					}
				}
			}

			//�o�ꂵ�Ă���e�ۂ𓮂���
			for (i = 0; i < MAX_SHOT; i++) {
				if (shot_life[i] > 0) {
					shot_y[i] -= 10;
					//�e�ۂ���ʊO�ɏo����폜����
					if (shot_y[i] < 0 - shot_ysize[i])
						shot_life[i] = 0;
				}
			}
			//�o�ꂵ�Ă���G�𓮂���
			for (i = 0; i < MAX_ENEMY; i++) {
				if (enemy_life[i] > 0) {
					enemy_y[i] += 3;
					//�G����ʊO�ɏo����폜����
					if (enemy_y[i] > 480)
						enemy_life[i] = 0;
				}
			}

			//�w�i���ړ�������
			back_y += 5;
			if (back_y >= 2400)
				back_y -= 2400;	//�w�i�̃��[�v

								//�G�ƒe�ۂ̓����蔻��
			for (i = 0; i < MAX_SHOT; i++) {
				if (shot_life[i] > 0) {
					for (j = 0; j < MAX_ENEMY; j++) {
						if (enemy_life[j] > 0) {
							if (shot_x[i] <= enemy_x[j] + enemy_xsize[j] && shot_x[i] + shot_xsize[i] >= enemy_x[j]) {
								if (shot_y[i] <= enemy_y[j] + enemy_ysize[j] && shot_y[i] + shot_ysize[i] >= enemy_y[j]) {
									//�������Ă�����A�e�ۂ��폜���ēG�̗̑͂�1���炷
									shot_life[i] = 0;
									enemy_life[j]--;
									//�G��|������X�R�A�𑝂₷
									if (enemy_life[j] == 0)
										score += 100;
								}
							}
						}
					}
				}
			}

			//�v���C���[�̃Z�[�t�^�C����1���炷
			if (player_safetime > 0)
				player_safetime--;
			//�G�ƃv���C���[�̓����蔻��
			if (player_safetime == 0) {
				for (i = 0; i < MAX_ENEMY; i++) {
					if (enemy_life[i] > 0) {
						if (enemy_x[i] <= player_x + player_xsize && enemy_x[i] + enemy_xsize[i] >= player_x) {
							if (enemy_y[i] <= player_y + player_ysize && enemy_y[i] + enemy_ysize[i] >= player_y) {
								//�v���C���[�̗̑͂�1���炵�A1�b�ԃ_���[�W���󂯂Ȃ��悤�ɂ���
								player_life--;
								player_safetime = 60;
							}
						}
					}
				}
			}

			//�v���C���[�̗̑͂�0�ȉ��ɂȂ�����Q�[���I�[�o�[
			if (player_life <= 0)
				mode = 2;
		}
		//�ϐ��umode�v��2�Ȃ�΁A�Q�[���I�[�o�\��ʂ̏���������
		else if (mode == GAMEOVER) {
			//Z�L�[�������ꂽ��^�C�g����ʂɖ߂�
			if (key_z == 1) {
				mode = 0;
				//��������̃X�R�A���ő�X�R�A��荂����΁A�ő�X�R�A���X�V
				if (score > max_score)
					max_score = score;
				FILE *wf;
				fopen_s(&wf, "Data/max_score.txt", "w");
				if (wf != NULL) {
					fwrite(&max_score, sizeof(int), 1, wf);
					fclose(wf);
				}
			}
		}

		//--------------�Q�[���̕`�������-----------------
		//�ϐ��umode�v��0�Ȃ�΁A�^�C�g����ʂ̕`�������
		if (mode == 0) {
			//������`�悷��
			DrawString(20, 20, "�^�C�g�����", GetColor(255, 255, 255));
			DrawFormatString(20, 60, GetColor(255, 255, 255), "�ő�X�R�A�F%d", max_score);
		}
		//�ϐ��umode�v��1�Ȃ�΁A���C����ʂ̕`�������
		else if (mode == 1) {
			//�w�i��`��
			DrawGraph(0, back_y, back_g, TRUE);
			DrawGraph(0, back_y - 2400, back_g, TRUE);

			//�e�ۂ�`��
			for (i = 0; i < MAX_SHOT; i++) {
				if (shot_life[i] > 0) {
					DrawGraph(shot_x[i], shot_y[i], shot_g, TRUE);
				}
			}
			//�G��`��
			for (i = 0; i < MAX_ENEMY; i++) {
				if (enemy_life[i] > 0) {
					DrawGraph(enemy_x[i], enemy_y[i], enemy_g, TRUE);
				}
			}
			

			//����`��
			DrawBox(0, 0, 440, 480, GetColor(0, 0, 255), FALSE);

			DrawString(460, 20, "score", GetColor(255, 255, 255));
			DrawFormatString(480, 40, GetColor(255, 255, 255), "%d", score);
			DrawString(460, 100, "life", GetColor(255, 255, 255));
			for (i = 0; i < player_life; i++) {
				DrawGraph(480 + i * 25, 120, plife_g, TRUE);
			}
			//TestMessage();
		}
		//�ϐ��umode�v��2�Ȃ�΁A�Q�[���I�[�o�\��ʂ̕`�������
		else if (mode == 2) {
			DrawString(20, 20, "Game Over", GetColor(255, 255, 255));
			DrawFormatString(20, 100, GetColor(255, 255, 255), "Total Score : %d", score);
		}*/

		ScreenFlip();
	}
	DeleteGraphicAll();
	DxLib_End();
	return 0;
}

void LoadGraphicAll() {
	LoadDivGraph("Data/pc01.png",2,2,1,48,48, player.graphic);
	for (int i = 0; i < MAX_KARASU; i++) {
		LoadDivGraph("Data/en01.png", 2, 2, 1, 48, 48, karasu[i].graphic);
	}
	player.life_graphic = LoadGraph("Data/life.bmp");
	tomato_graphic = LoadGraph("Data/tomato.png");
	backbround_graphic[0] = LoadGraph("Data/inaka.png");
	backbround_graphic[1] = LoadGraph("Data/hatake.png");
}

void DeleteGraphicAll() {
	DeleteGraph(player.graphic[0]);
	DeleteGraph(player.graphic[1]);
	DeleteGraph(player.life_graphic);
	DeleteGraph(tomato_graphic);
	DeleteGraph(backbround_graphic[0]);
	DeleteGraph(backbround_graphic[1]);
	for (int i = 0; i < MAX_KARASU; i++) {
		DeleteGraph(karasu[i].graphic[0]);
		DeleteGraph(karasu[i].graphic[1]);
	}
}

void TestMessage() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�ϐ� mode �̒l�� %d �ł�", mode);
}