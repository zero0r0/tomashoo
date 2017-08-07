#include "Key.h"
#include "DxLib.h"
#include "data.h"

int gameover_state = 0;

//�U���G�b�O�ύX
int score_count = 0;
int end_count = 0;
int score = 0;
int max_score = 0;

//�U���G�b�O�ύX
//�ő�X�R�A�̓ǂݍ���
void LoadMaxScore() {
	FILE* rf;
	//�t�@�C����ǂݍ���
	fopen_s(&rf, "Data/max_score.txt", "r");
	//�t�@�C���̓ǂݍ��݂ɐ���������A��������l��ǂݍ���
	if (rf != NULL) {
		fread(&max_score, sizeof(int), 1, rf);
		fclose(rf);	//�t�@�C�������
	}
}

//�Q�[���I�[�o�[���Ăяo���ꂽ�Ƃ��̏���������
void GameoverInit(int n) {
	StopSoundMem(stage_bgm[0]);
	StopSoundMem(stage_bgm[1]);
	gameover_state = n;
	if (n == 3)
		PlaySoundMem(gameover_bgm[1], DX_PLAYTYPE_BACK, true);
	else
		PlaySoundMem(gameover_bgm[0], DX_PLAYTYPE_BACK, true);
	
	scene = GAMEOVER;
}

void GameClearInit() {
	StopSoundMem(stage_bgm[0]);
	StopSoundMem(stage_bgm[1]);

	scene = CLEAR;
	
	score_count = 0;
	end_count = 0;

	//�U���G�b�O�ύX
	score = player.time * 10 + player.tomato * (10 - weather_number);
	if (score > max_score)  //�n�C�X�R�A�X�V���̃X�R�A�ۑ�
		max_score = score;
	FILE *wf;
	fopen_s(&wf, "Data/max_score.txt", "w");
	if (wf != NULL) {
		fwrite(&max_score, sizeof(int), 1, wf);
		fclose(wf);
	}
}

//�Q�[���I�[�o�[�X�V���鏈��������
void GameoverUpdate() {
	if (key_z == 1) {
		StopSoundMem(gameover_bgm[0]);
		StopSoundMem(gameover_bgm[1]);

		TitleInit();
		scene = TITLE;
	}
}

//�Q�[���N���A�X�V���鏈��������
void GameClearUpdate() {

	if (key_z == 1) {
		score_count = 1;
		end_count += 1;
	}

	if (end_count == 2) {
		TitleInit();
		scene = TITLE;
	}
}

//�Q�[���N���A���̕`�揈��
void GameClearDraw() {
	DrawGraph(0,0,gameclear_graphic,true);

	//�U���G�b�O�ύX
	if (score_count == 1) {
		//SetFontSize(50);
		//DrawFormatString(180, 100, GetColor(0, 0, 0), "�^�C���@ %4d", player.time);
		//DrawFormatString(180, 175, GetColor(0, 0, 0), "�g�}�g�@ %4d", player.tomato);
		//DrawFormatString(180, 250, GetColor(0, 0, 0), "�X�R�A�@ %4d", score);
		DrawFormatStringToHandle(180, 100, GetColor(255, 0, 0),font_handle[3],"�^�C��");
		DrawGraph(480, 100, font_num_graphic[player.time % 10], true);
		DrawGraph(445, 100, font_num_graphic[(player.time / 10) % 10], true);
		DrawFormatStringToHandle(180, 175, GetColor(255, 0, 0), font_handle[3], "�g�}�g");
		DrawGraph(480, 175, font_num_graphic[player.tomato % 10], true);
		DrawGraph(445, 175, font_num_graphic[(player.tomato / 10) % 10], true);
		DrawGraph(410, 175, font_num_graphic[(player.tomato / 100) % 10], true);
		DrawFormatStringToHandle(180, 250, GetColor(255, 0, 0), font_handle[3], "�X�R�A");
		DrawGraph(480, 250, font_num_graphic[score % 10], true);
		DrawGraph(445, 250, font_num_graphic[(score / 10) % 10], true);
		DrawGraph(410, 250, font_num_graphic[(score / 100) % 10], true);
		DrawGraph(375, 250, font_num_graphic[(score / 1000) % 10], true);
	}
}

//�Q�[���I�[�o�[�ł̕`�揈��
void GameoverDraw() {
	DrawGraph(0,0,gameover_graphic[gameover_state],true);
}