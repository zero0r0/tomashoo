#pragma once

#define MAX_TOMATO 255
#define MAX_ENEMY 1
#define STAGE_NUM 2

/*オブジェクト系*/
typedef struct {
	int graphic[2];			//プレイヤー画像
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
	int life;				//ライフ
	int life_graphic;		//ライフの画像
	int safetime;			//無敵時間
	int shot_trigger;		//ショットのインターバル
	int tomato;				//所持トマト数
	int speed;
}Player;

typedef struct {
	int life;
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
}Shot;

typedef struct {
	bool is_dead;
	int graphic[2];
	int start_x, start_y;		//スタートするポジション
	int x, y;					
	int x_size, y_size;
	int speed;
}Enemy;

typedef struct {
	int x, y;
	int x_size, y_size;
}Item;

typedef struct {
	int x, y;
	int x_size, y_size;
	int graphic;
	int loopNum;	//ループ回数
}Background;


void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerMovement();
void PlayerShot();
void PlayerCollision();
void PlayerSpeedUp();
void PlayerSpeedDown();

void EnemyInit();
void EnemyUpdate();
void EnemyDraw();

void ShotInit();
void ShotUpdate();

void BackgroundInit();
void BackgroundUpdate();
void BackgroundDraw();

void TitleInit();
void TitleUpdata();
void TitleDraw();

void MainGameInit();
void MainGameUpdate();
void MainGameDraw();

//int Lerp(int,int,int,int,int);

extern Player player;
extern Shot shot[MAX_TOMATO];
extern Item item[MAX_TOMATO];
extern Enemy enemy[MAX_ENEMY];
extern Background background[STAGE_NUM];


/*グラフィック系*/
extern int shot_graphic;
extern int tomato_graphic;
extern int speed_meter_graphic;
extern int speed_needle_graphic;

//extern int backbround_graphic[STAGE_NUM];
//extern int karasu_graphic;



/*「mode」
ゲームには、タイトル画面、メイン画面（ゲーム画面）、ゲームオーバー画面など、さまざまな画面がある。
変数「mode」に現在の状態を入れておくことで、画面の切り替えができる。
例えば、「mode」が0ならタイトル画面を描画、1ならメイン画面の描画、2ならゲームオーバ―画面の描画をする。
最初はタイトル画面なので、初期値として0を入れておく。*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int mode;

/*----------FPS関連-----------------*/

extern int mStartTime;      //測定開始時刻
extern int mCount;          //カウンタ
extern float mFps;          //fps
extern const int N;	//平均を取るサンプル数
extern const int FPS;	//設定したFPS