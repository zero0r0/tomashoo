#include "DxLib.h"
#include "Key.h"
#include "data.h"

#define WINDOW_XSIZE 640
#define WINDOW_YSIZE 480


void TestMessage();		//関数のプロトタイプ宣言
void LoadGraphicAll();
void DeleteGraphicAll();


Player player;
Shot shot[MAX_TOMATO];
Item item[MAX_TOMATO];
Enemy enemy[MAX_ENEMY];
Background background[STAGE_NUM];

int mode;
int const TITLE = 0;
int const MAIN = 1;
int const GAMEOVER = 2;

//グラフィック系
int shot_graphic;
int tomato_graphic;
int speed_meter_graphic;
int speed_needle_graphic;

/*----------FPS関連-----------------*/

int mStartTime;      //測定開始時刻
int mCount;          //カウンタ
float mFps;          //fps
const int N = 60;	//平均を取るサンプル数
const int FPS = 60;	//設定したFPS

bool Update() {
	if (mCount == 0) { //1フレーム目なら時刻を記憶
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60フレーム目なら平均を計算する
		int t = GetNowCount();
		mFps = 1000.f / ((t - mStartTime) / (float)N);
		mCount = 0;
		mStartTime = t;
	}
	mCount++;
	return true;
}

void Draw() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "%.1f", mFps);
}

void Wait() {
	int tookTime = GetNowCount() - mStartTime;	//かかった時間
	int waitTime = mCount * 1000 / FPS - tookTime;	//待つべき時間
	if (waitTime > 0) {
		Sleep(waitTime);	//待機
	}
}

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
	
	LoadGraphicAll();

	mode = TITLE;
	TitleInit();

	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		Update();
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
		Draw();
		ScreenFlip();
		Wait();
	}
	DeleteGraphicAll();
	DxLib_End();
	return 0;
}

void LoadGraphicAll() {
	LoadDivGraph("Data/pc01.png",2,2,1,48,48, player.graphic);
	for (int i = 0; i < MAX_ENEMY; i++) {
		LoadDivGraph("Data/en01.png", 2, 2, 1, 48, 48, enemy[i].graphic);
	}
	player.life_graphic = LoadGraph("Data/life.bmp");
	tomato_graphic = LoadGraph("Data/bl01.png");
	background[0].graphic = LoadGraph("Data/inaka.png");
	background[1].graphic = LoadGraph("Data/hatake.png");
	speed_meter_graphic = LoadGraph("Data/speed_meter.png");
	speed_needle_graphic = LoadGraph("Data/speed_needle.png");
}

void DeleteGraphicAll() {
	DeleteGraph(player.graphic[0]);
	DeleteGraph(player.graphic[1]);
	DeleteGraph(player.life_graphic);
	DeleteGraph(tomato_graphic);
	for(int i = 0; i < STAGE_NUM;i++)
		DeleteGraph(background[i].graphic);
	for (int i = 0; i < MAX_ENEMY; i++) {
		DeleteGraph(enemy[i].graphic[0]);
		DeleteGraph(enemy[i].graphic[1]);
	}
	DeleteGraph(speed_meter_graphic);
	DeleteGraph(speed_needle_graphic);
}

void TestMessage() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "変数 mode の値は %d です", mode);
}