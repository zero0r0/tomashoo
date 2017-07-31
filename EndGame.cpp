#include "Key.h"
#include "DxLib.h"
#include "data.h"

int gameover_state = 0;

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
		TitleInit();
		scene = TITLE;
	}
}

//�Q�[���N���A���̕`�揈��
void GameClearDraw() {
	DrawGraph(0,0,gameclear_graphic,true);
}

//�Q�[���I�[�o�[�ł̕`�揈��
void GameoverDraw() {
	DrawGraph(0,0,gameover_graphic[gameover_state],true);
}