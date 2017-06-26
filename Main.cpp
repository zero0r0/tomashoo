#include "DxLib.h"
#include "Key.h"
#include "data.h"

#define WINDOW_XSIZE 640
#define WINDOW_YSIZE 480


void TestMessage();		//関数のプロトタイプ宣言
void LoadGraphic();

Player player;
Shot shot[MAX_TOMATO];

int mode;
int const TITLE = 0;
int const MAIN = 1;
int const GAMEOVER = 2;

//グラフィック系
int shot_graphic;
int tomato_graphic;

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hp, LPSTR lpC, int nC) {

	/*----------------↓基本的な設定----------------------
	基本的な設定はどのゲームでもほぼコピペなので、
	意味はあまり気にしなくておっけー
	*/
	ChangeWindowMode(TRUE);					//ウィンドウモードにする
	SetMainWindowText("テストゲーム");		//ウィンドウのタイトルを変更する
	SetWindowSizeChangeEnableFlag(FALSE);
	SetGraphMode(WINDOW_XSIZE, WINDOW_YSIZE, 32);				//ウィンドウのサイズを640x480にする
	SetWindowSizeExtendRate(1);

	if (DxLib_Init() == -1) return -1;		//Dxライブラリを初期化する
	SetOutApplicationLogValidFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);			//描画対象を裏画面にする

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);  //フォントの設定
	SetFontSize(18);

	/*----------------↑基本的な設定----------------------*/

	//背景の情報いろいろ
	int back_y;
	int back_g = LoadGraph("Data/back.bmp");

	//ゲームの情報いろいろ
	int score;
	int max_score = 0;

	FILE* rf;
	//ファイルを読み込む
	fopen_s(&rf, "Data/max_score.txt", "r");
	//ファイルの読み込みに成功したら、そこから値を読み込む
	if (rf != NULL) {
		fread(&max_score, sizeof(int), 1, rf);
		fclose(rf);	//ファイルを閉じる
	}

	mode = TITLE;
	TitleInit();

	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		KeyUpdate();
		//--------------ゲームの処理をする-----------------
		//変数「mode」が0ならば、タイトル画面の処理をする
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
			

			//トリガーを-1する
			shot_trigger--;
			//Zキーが押されていて、かつトリガーが0以下だったら弾丸を発射する
			if (key_z > 0 && shot_trigger <= 0) {
				//使用されていない弾丸を探し、見つけたら情報をセットして抜け出す
				for (i = 0; i < MAX_SHOT; i++) {
					if (shot_life[i] == 0) {
						shot_life[i] = 1;
						shot_xsize[i] = 20;
						shot_ysize[i] = 20;
						shot_x[i] = player_x + player_xsize / 2 - shot_xsize[i] / 2;
						shot_y[i] = player_y;

						//トリガーを設定
						shot_trigger = 10;
						break;		//ループから脱出
					}
				}
			}
			//乱数を使用して、1/20の確率で敵を出現させる
			//※1ループにつき1/20、60ループ/1秒のため、だいたい敵が1秒で3体出る計算となる
			if (GetRand(20) == 0) {
				//使用されていない敵を探し、見つけたら情報をセットして抜け出す
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

			//登場している弾丸を動かす
			for (i = 0; i < MAX_SHOT; i++) {
				if (shot_life[i] > 0) {
					shot_y[i] -= 10;
					//弾丸が画面外に出たら削除する
					if (shot_y[i] < 0 - shot_ysize[i])
						shot_life[i] = 0;
				}
			}
			//登場している敵を動かす
			for (i = 0; i < MAX_ENEMY; i++) {
				if (enemy_life[i] > 0) {
					enemy_y[i] += 3;
					//敵が画面外に出たら削除する
					if (enemy_y[i] > 480)
						enemy_life[i] = 0;
				}
			}

			//背景を移動させる
			back_y += 5;
			if (back_y >= 2400)
				back_y -= 2400;	//背景のループ

								//敵と弾丸の当たり判定
			for (i = 0; i < MAX_SHOT; i++) {
				if (shot_life[i] > 0) {
					for (j = 0; j < MAX_ENEMY; j++) {
						if (enemy_life[j] > 0) {
							if (shot_x[i] <= enemy_x[j] + enemy_xsize[j] && shot_x[i] + shot_xsize[i] >= enemy_x[j]) {
								if (shot_y[i] <= enemy_y[j] + enemy_ysize[j] && shot_y[i] + shot_ysize[i] >= enemy_y[j]) {
									//当たっていたら、弾丸を削除して敵の体力を1減らす
									shot_life[i] = 0;
									enemy_life[j]--;
									//敵を倒したらスコアを増やす
									if (enemy_life[j] == 0)
										score += 100;
								}
							}
						}
					}
				}
			}

			//プレイヤーのセーフタイムを1減らす
			if (player_safetime > 0)
				player_safetime--;
			//敵とプレイヤーの当たり判定
			if (player_safetime == 0) {
				for (i = 0; i < MAX_ENEMY; i++) {
					if (enemy_life[i] > 0) {
						if (enemy_x[i] <= player_x + player_xsize && enemy_x[i] + enemy_xsize[i] >= player_x) {
							if (enemy_y[i] <= player_y + player_ysize && enemy_y[i] + enemy_ysize[i] >= player_y) {
								//プレイヤーの体力を1減らし、1秒間ダメージを受けないようにする
								player_life--;
								player_safetime = 60;
							}
						}
					}
				}
			}

			//プレイヤーの体力が0以下になったらゲームオーバー
			if (player_life <= 0)
				mode = 2;
		}
		//変数「mode」が2ならば、ゲームオーバ―画面の処理をする
		else if (mode == GAMEOVER) {
			//Zキーが押されたらタイトル画面に戻る
			if (key_z == 1) {
				mode = 0;
				//もし今回のスコアが最大スコアより高ければ、最大スコアを更新
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

		//--------------ゲームの描画をする-----------------
		//変数「mode」が0ならば、タイトル画面の描画をする
		if (mode == 0) {
			//文字を描画する
			DrawString(20, 20, "タイトル画面", GetColor(255, 255, 255));
			DrawFormatString(20, 60, GetColor(255, 255, 255), "最大スコア：%d", max_score);
		}
		//変数「mode」が1ならば、メイン画面の描画をする
		else if (mode == 1) {
			//背景を描画
			DrawGraph(0, back_y, back_g, TRUE);
			DrawGraph(0, back_y - 2400, back_g, TRUE);

			//弾丸を描画
			for (i = 0; i < MAX_SHOT; i++) {
				if (shot_life[i] > 0) {
					DrawGraph(shot_x[i], shot_y[i], shot_g, TRUE);
				}
			}
			//敵を描画
			for (i = 0; i < MAX_ENEMY; i++) {
				if (enemy_life[i] > 0) {
					DrawGraph(enemy_x[i], enemy_y[i], enemy_g, TRUE);
				}
			}
			

			//淵を描画
			DrawBox(0, 0, 440, 480, GetColor(0, 0, 255), FALSE);

			DrawString(460, 20, "score", GetColor(255, 255, 255));
			DrawFormatString(480, 40, GetColor(255, 255, 255), "%d", score);
			DrawString(460, 100, "life", GetColor(255, 255, 255));
			for (i = 0; i < player_life; i++) {
				DrawGraph(480 + i * 25, 120, plife_g, TRUE);
			}
			//TestMessage();
		}
		//変数「mode」が2ならば、ゲームオーバ―画面の描画をする
		else if (mode == 2) {
			DrawString(20, 20, "Game Over", GetColor(255, 255, 255));
			DrawFormatString(20, 100, GetColor(255, 255, 255), "Total Score : %d", score);
		}*/

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

void LoadGraphic() {
	player.graphic = LoadGraph("Data/player.bmp");
	player.life_graphic = LoadGraph("Data/life.bmp");

}

void DeleteGraphicAll() {
	DeleteGraph(player.graphic);
	DeleteGraph(player.life_graphic);
}

void TestMessage() {
	DrawString(0, 0, "Shooting Game!!", GetColor(255, 255, 255));
}