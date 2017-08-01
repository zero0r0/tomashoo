#pragma once

#define MAX_TOMATO 255
#define MAX_ITEM 8
#define MAX_ENEMY 125
#define ENEMY_SPAWN_NUM 5
#define MAX_ENEMY_TYPE 11
#define MAX_STAGE 4
#define CHANGE_BACKGROUND_BY_LOOP_NUM 3
#define ENEMY_ANIMETION_NUM 2	//敵のアニメーションの画像数
#define PI    3.1415926535897932384626433832795f
#define EFFECT_NUM 25
#define BEGINING_MOVE_Y -25
#define TIME_LIMIT 60

/*オブジェクト系*/
typedef struct {
	int graphic[2][2];		//プレイヤー画像
	int x, y;				//xy座標
	int width_speed;
	int x_size, y_size;		//x.y大きさ
	int safetime;			//無敵時間
	int shot_trigger;		//ショットのインターバル
	int tomato;				//所持トマト数
	int speed;
	int anim_count;			//countが一定数たまったら++する
	int count;				//マイフレームカウントしていく
	int r;
	//25日エッグ変更
	int time;
	int fleam_count;
}Player;

typedef struct {
	//int life;	
	bool is_active;
	int x, y;				//xy座標
	int x_size, y_size;		//x.y大きさ
	int r;
}Shot;

typedef struct {
	//bool is_appeared;		//出現したかどうか
	bool is_dead;			//しんだ、画面外か
	int state;				//どのアニメーション画像のステートか
	int count;
	int x, y;					
	int x_size, y_size;
	int type;				//1:カラス、2:はくび、3:イノシシ 4.歩行,5,不良
	int move_x;				
	int move_y;				
	int r;
}Enemy;

typedef struct {
	int x, y;
	int x_size, y_size;
	int r;
	int state;	//アニメーションの状態
	int count;	//アニメーション時のカウント
}Item;

typedef struct {
	int x, y;
	int x_size, y_size;
	int now_stage;
	int loopNum;			//ループ回数
}Background;

typedef struct{
	int x, y;
	int state;	//アニメーションの状態
	int count;	//アニメーション時のカウント
	bool is_used;
}Effect;


void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerMovement();
void PlayerShot();
void PlayerCollision();
void PlayerSpeedUp();
void PlayerSpeedDown();
void Damage(int);

void EnemyInit();
void EnemyUpdate();
void EnemyDraw();
//void EnemyLoad();
void SpawnEnemy(int,int, int);
void SpawnEffect(int, int);
int EnemyTypeSearch(int);

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

void GameoverInit(int);
void GameoverUpdate();
void GameoverDraw();

void GameClearInit();
void GameClearUpdate();
void GameClearDraw();


//int Lerp(int,int,int,int,int);

extern Player player;
extern Shot shot[MAX_TOMATO];
extern Item item[MAX_TOMATO];
extern Enemy enemy[MAX_ENEMY];
extern Background background[2];
extern Effect tomato_effect[MAX_TOMATO];



/*グラフィック系*/
extern int tomato_item_graphic[2];
extern int shot_graphic;
extern int speed_meter_graphic;
extern int speed_needle_graphic;
extern int font_num_graphic[10];
extern int font_tomato_graphic;
extern int shasen_graphic;
extern int background_graphic[MAX_STAGE];
extern int enemy_graphic[MAX_ENEMY_TYPE][ENEMY_ANIMETION_NUM];
extern int weather_graphic[3];
extern int tomato_effect_graphic[2];
extern int sand_effect_graphic[2];
extern int font_timeup_graphic[4];
extern int weather_number;
extern int font_length_graphic[2];
extern int gameover_graphic[4];
extern int gameclear_graphic;

//サウンド系
extern int stage_bgm[2];
extern int gameover_bgm[2];


/*「scene」
ゲームには、タイトル画面、メイン画面（ゲーム画面）、ゲームオーバー画面など、さまざまな画面がある。
変数「scene」に現在の状態を入れておくことで、画面の切り替えができる。
例えば、「scene」が0ならタイトル画面を描画、1ならメイン画面の描画、2ならゲームオーバ―画面の描画をする。
最初はタイトル画面なので、初期値として0を入れておく。*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int const CLEAR;
extern int scene;

extern int total_distance;
//30日エッグ変更
extern int length;     //距離
extern double timer;

/*----------FPS関連-----------------*/

extern int mStartTime;      //測定開始時刻
extern int mCount;          //カウンタ
extern float mFps;          //fps
extern const int N;	//平均を取るサンプル数
extern const int FPS;	//設定したFPS

extern bool is_clear;
extern bool last_stage;
extern int now_wave;
