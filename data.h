#pragma once

#define MAX_TOMATO 255
#define MAX_ITEM 5
#define MAX_ENEMY 25
#define MAX_ENEMY_TYPE 5
#define MAX_STAGE 2
#define CHANGE_BACKGROUND_BY_LOOP_NUM 5
#define ENEMY_ANIMETION_NUM 2	//敵のアニメーションの画像数
#define PI    3.1415926535897932384626433832795f

/*オブジェクト系*/
typedef struct {
	int graphic[2];			//プレイヤー画像
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
	int life;				//ライ
	int life_graphic;		//ライフの画像
	int safetime;			//無敵時間
	int shot_trigger;		//ショットのインターバル
	int tomato;				//所持トマト数
	int speed;
	int anim_count;			//countが一定数たまったら++する
	int count;				//マイフレームカウントしていく
	int r;
}Player;

typedef struct {
	int life;	
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
	int r;
}Shot;

typedef struct {
	bool is_appeared;		//出現したかどうか
	bool is_dead;			//しんだ、画面外か
	//int graphic[2];
	int state;				//どのアニメーション画像のステートか
	int x, y;					
	int x_size, y_size;
	int wait_time;			//出現時間
	int type;				//1:カラス、2:はくび、3:イノシシ 4.歩行,5,不良
	int move_x;
	int move_y;
	int r;
}Enemy;

typedef struct {
	int x, y;
	int x_size, y_size;
	int r;
}Item;

typedef struct {
	int x, y;
	int x_size, y_size;
	int now_stage;
	int loopNum;			//ループ回数
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
void EnemyLoad();
void SpawnEnemy();

void ShotInit();
void ShotUpdate();

void ItemInit();
void SpawnItem(int);
void ItemUpdate();
void ItemDraw();

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
extern Background background[2];


/*グラフィック系*/
extern int tomato_graphic;
extern int shot_graphic;
extern int speed_meter_graphic;
extern int speed_needle_graphic;
extern int font_num_graphic[10];
extern int font_tomato_graphic;
extern int shasen_graphic;
extern int background_graphic[MAX_STAGE];
extern int enemy_graphic[MAX_ENEMY_TYPE][ENEMY_ANIMETION_NUM];
extern int weather_graphic[3];


/*「mode」
ゲームには、タイトル画面、メイン画面（ゲーム画面）、ゲームオーバー画面など、さまざまな画面がある。
変数「mode」に現在の状態を入れておくことで、画面の切り替えができる。
例えば、「mode」が0ならタイトル画面を描画、1ならメイン画面の描画、2ならゲームオーバ―画面の描画をする。
最初はタイトル画面なので、初期値として0を入れておく。*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int mode;

extern double total_distance;
extern double timer;

/*----------FPS関連-----------------*/

extern int mStartTime;      //測定開始時刻
extern int mCount;          //カウンタ
extern float mFps;          //fps
extern const int N;	//平均を取るサンプル数
extern const int FPS;	//設定したFPS