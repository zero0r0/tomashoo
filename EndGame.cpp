#include "Key.h"
#include "DxLib.h"
#include "data.h"

int gameover_state = 0;

//６日エッグ変更
int score_count = 0;
int end_count = 0;
int score = 0;
int max_score = 0;

//６日エッグ変更
//最大スコアの読み込み
void LoadMaxScore() {
	FILE* rf;
	//ファイルを読み込む
	fopen_s(&rf, "Data/max_score.txt", "r");
	//ファイルの読み込みに成功したら、そこから値を読み込む
	if (rf != NULL) {
		fread(&max_score, sizeof(int), 1, rf);
		fclose(rf);	//ファイルを閉じる
	}
}

//ゲームオーバーが呼び出されたときの処理を書く
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

	//６日エッグ変更
	score = player.time * 10 + player.tomato * (10 - weather_number);
	if (score > max_score)  //ハイスコア更新字のスコア保存
		max_score = score;
	FILE *wf;
	fopen_s(&wf, "Data/max_score.txt", "w");
	if (wf != NULL) {
		fwrite(&max_score, sizeof(int), 1, wf);
		fclose(wf);
	}
}

//ゲームオーバー更新する処理を書く
void GameoverUpdate() {
	if (key_z == 1) {
		StopSoundMem(gameover_bgm[0]);
		StopSoundMem(gameover_bgm[1]);

		TitleInit();
		scene = TITLE;
	}
}

//ゲームクリア更新する処理を書く
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

//ゲームクリア時の描画処理
void GameClearDraw() {
	DrawGraph(0,0,gameclear_graphic,true);

	//６日エッグ変更
	if (score_count == 1) {
		//SetFontSize(50);
		//DrawFormatString(180, 100, GetColor(0, 0, 0), "タイム　 %4d", player.time);
		//DrawFormatString(180, 175, GetColor(0, 0, 0), "トマト　 %4d", player.tomato);
		//DrawFormatString(180, 250, GetColor(0, 0, 0), "スコア　 %4d", score);
		DrawFormatStringToHandle(180, 100, GetColor(255, 0, 0),font_handle[3],"タイム");
		DrawGraph(480, 100, font_num_graphic[player.time % 10], true);
		DrawGraph(445, 100, font_num_graphic[(player.time / 10) % 10], true);
		DrawFormatStringToHandle(180, 175, GetColor(255, 0, 0), font_handle[3], "トマト");
		DrawGraph(480, 175, font_num_graphic[player.tomato % 10], true);
		DrawGraph(445, 175, font_num_graphic[(player.tomato / 10) % 10], true);
		DrawGraph(410, 175, font_num_graphic[(player.tomato / 100) % 10], true);
		DrawFormatStringToHandle(180, 250, GetColor(255, 0, 0), font_handle[3], "スコア");
		DrawGraph(480, 250, font_num_graphic[score % 10], true);
		DrawGraph(445, 250, font_num_graphic[(score / 10) % 10], true);
		DrawGraph(410, 250, font_num_graphic[(score / 100) % 10], true);
		DrawGraph(375, 250, font_num_graphic[(score / 1000) % 10], true);
	}
}

//ゲームオーバーでの描画処理
void GameoverDraw() {
	DrawGraph(0,0,gameover_graphic[gameover_state],true);
}