#pragma once

#define MAX_TOMATO 255

/*オブジェクト系*/
typedef struct {
	int graphic;			//プレイヤー画像
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
	int life;				//ライフ
	int life_graphic;		//ライフの画像
	int safetime;			//無敵時間
	int shot_trigger;		//ショットのインターバル
	int tomato;				//所持トマト数
}Player;

typedef struct {
	int life;
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
}Shot;

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerMovement();
void PlayerShot();

void TitleInit();
void TitleUpdata();
void TitleDraw();

void MainGameInit();
void MainGameUpdate();
void MainGameDraw();


extern Player player;
extern Shot shot[MAX_TOMATO];

/*グラフィック系*/
extern int shot_graphic;
extern int tomato_grahic;

/*「mode」
ゲームには、タイトル画面、メイン画面（ゲーム画面）、ゲームオーバー画面など、さまざまな画面がある。
変数「mode」に現在の状態を入れておくことで、画面の切り替えができる。
例えば、「mode」が0ならタイトル画面を描画、1ならメイン画面の描画、2ならゲームオーバ―画面の描画をする。
最初はタイトル画面なので、初期値として0を入れておく。*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int mode;
