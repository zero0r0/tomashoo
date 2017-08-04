#include "DxLib.h"
#include "Key.h"
#include "data.h"

#define WINDOW_XSIZE 640
#define WINDOW_YSIZE 480


void LoadGraphicAll();
void DeleteGraphicAll();
void LoadSoundAll();
void DeleteSoundAll();


Player player;
Shot shot[MAX_TOMATO];
Item item[MAX_TOMATO];
Enemy enemy[MAX_ENEMY];
Background background[2];

int scene;
int const TITLE = 0;
int const MAIN = 1;
int const GAMEOVER = 2;
int const CLEAR = 3;

bool is_clear = false;
bool is_exit = false;
int weather_number;

//グラフィック系
int shot_graphic;
int tomato_item_graphic[2];
int speed_meter_graphic;
int speed_needle_graphic;
int background_graphic[MAX_STAGE];
int enemy_graphic[MAX_ENEMY_TYPE][ENEMY_ANIMETION_NUM];
int weather_graphic[3];
int font_num_graphic[10];
int font_tomato_graphic;
int shasen_graphic;
int tomato_effect_graphic[2];
int sand_effect_graphic[2];
int gameover_graphic[4];
//25日エッグ変更
int font_timeup_graphic[4];
int font_length_graphic[2];
int gameclear_graphic;

//タイトルで使うグラフィック系
int titlelogo_graphic[3];
int title_botton_graphic[3];
int title_tomato_graphic[2];
int title_conbea_graphic;
int title_pushed_tomato_graphic;

//サウンド系
int stage_bgm[2];
int gameover_bgm[2];
int title_bgm;

int crash_se;
int warning_se;
int get_se;
int tubure_se;
int nageru_se;

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
	LoadSoundAll();

	scene = TITLE;
	TitleInit();

	//メインループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && !is_exit) {
		Update();
		ClearDrawScreen();
		KeyUpdate();
		//--------------ゲームの処理をする-----------------
		//変数「scene」が0ならば、タイトル画面の処理をする
		switch (scene) {
			case TITLE:
				TitleUpdata();
				TitleDraw();
				break;
			case MAIN:
				MainGameUpdate();
				MainGameDraw();
				break;
			case GAMEOVER:
				GameoverUpdate();
				GameoverDraw();
				break;
			case CLEAR:
				GameClearUpdate();
				GameClearDraw();
				break;
			default:
				break;
		}
		Draw();
		ScreenFlip();
		Wait();
	}
	//DeleteGraphicAll();
	InitGraph();
	InitSoundMem();
	//DeleteSoundAll();

	DxLib_End();
	return 0;
}

void LoadGraphicAll() {
	//30日エッグ変更
	LoadDivGraph("Data/pc01.png", 2, 2, 1, 48, 48, player.graphic[0]);
	LoadDivGraph("Data/pc02.png", 2, 2, 1, 48, 48, player.graphic[1]);
	LoadDivGraph("Data/en01.png", 2, 2, 1, 48, 48, enemy_graphic[0]);
	LoadDivGraph("Data/en02.png", 2, 2, 1, 48, 48, enemy_graphic[1]);
	LoadDivGraph("Data/en03.png", 2, 2, 1, 48, 48, enemy_graphic[2]);
	LoadDivGraph("Data/en04.png", 2, 2, 1, 48, 48, enemy_graphic[3]);
	LoadDivGraph("Data/en05c.png", 2, 2, 1, 48, 48, enemy_graphic[4]);
	LoadDivGraph("Data/en05l.png", 2, 2, 1, 48, 48, enemy_graphic[5]);
	LoadDivGraph("Data/en05r.png", 2, 2, 1, 48, 48, enemy_graphic[6]);
	
	for (int i = 0; i < 2; i++) {
		enemy_graphic[7][i] = LoadGraph("Data/en06b.png");
		enemy_graphic[8][i] = LoadGraph("Data/en06f.png");
		enemy_graphic[9][i] = LoadGraph("Data/en06r.png");
		enemy_graphic[10][i] = LoadGraph("Data/en06l.png");
	}

	//25日エッグ変更
	font_timeup_graphic[0] = LoadGraph("Data/font.timeup.png");
	font_timeup_graphic[1] = LoadGraph("Data/font.made.png");
	font_timeup_graphic[2] = LoadGraph("Data/font.ato.png");
	font_timeup_graphic[3] = LoadGraph("Data/font_hun.png");
	//
	
	shot_graphic = LoadGraph("Data/bl01.png");
	background_graphic[0] = LoadGraph("Data/inaka.png");
	background_graphic[1] = LoadGraph("Data/hatake.png");
	background_graphic[2] = LoadGraph("Data/road.png");
	background_graphic[3] = LoadGraph("Data/families.png");
	speed_meter_graphic = LoadGraph("Data/speed_meter.png");
	speed_needle_graphic = LoadGraph("Data/speed_needle.png");
	weather_graphic[0] = LoadGraph("Data/weather_rainy.png");
	weather_graphic[1] = LoadGraph("Data/weather_cloudy.png");
	weather_graphic[2] = LoadGraph("Data/weather_sunny.png");
	font_num_graphic[0] = LoadGraph("Data/font0.png");
	font_num_graphic[1] = LoadGraph("Data/font1.png");
	font_num_graphic[2] = LoadGraph("Data/font2.png");
	font_num_graphic[3] = LoadGraph("Data/font3.png");
	font_num_graphic[4] = LoadGraph("Data/font4.png");
	font_num_graphic[5] = LoadGraph("Data/font5.png");
	font_num_graphic[6] = LoadGraph("Data/font6.png");
	font_num_graphic[7] = LoadGraph("Data/font7.png");
	font_num_graphic[8] = LoadGraph("Data/font8.png");
	font_num_graphic[9] = LoadGraph("Data/font9.png");
	font_tomato_graphic = LoadGraph("Data/font.tomato.png");
	shasen_graphic = LoadGraph("Data/shasen.png");
	font_length_graphic[0] = LoadGraph("Data/font.nokori.png");
	//30日エッグ変更
	font_length_graphic[1] = LoadGraph("Data/font.km.png");
	LoadDivGraph("Data/it01.png", 2, 2, 1, 48, 48, tomato_item_graphic);
	LoadDivGraph("Data/ef02.png", 2, 2, 1, 48, 48, sand_effect_graphic);
	LoadDivGraph("Data/ef01.png", 2, 2, 1, 48, 48, tomato_effect_graphic);

	gameover_graphic[0] = LoadGraph("Data/gameover1.png");
	gameover_graphic[1] = LoadGraph("Data/gameover2.png");
	gameover_graphic[2] = LoadGraph("Data/gameover3.png");
	gameover_graphic[3] = LoadGraph("Data/gameover4.png");
	gameclear_graphic = LoadGraph("Data/gameclear.png");

	titlelogo_graphic[0] = LoadGraph("Data/font_to.png");
	titlelogo_graphic[1] = LoadGraph("Data/font_ma.png");
	titlelogo_graphic[2] = LoadGraph("Data/font_shu.png");
	
	title_botton_graphic[0] = LoadGraph("Data/botan_start.png");
	title_botton_graphic[1] = LoadGraph("Data/botan_record.png");
	title_botton_graphic[2] = LoadGraph("Data/botan_exit.png");

	title_tomato_graphic[0] = LoadGraph("Data/tomato.png");
	title_tomato_graphic[1] = LoadGraph("Data/tubureta_tomato.png");

	title_pushed_tomato_graphic = LoadGraph("Data/pushed_tomato.png");
	title_conbea_graphic = LoadGraph("Data/conveyor.png");
}

void DeleteGraphicAll() {
	//DeleteGraph(player.graphic[0]);
	//DeleteGraph(player.graphic[1]);
	// 30日エッグ変更
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			DeleteGraph(player.graphic[i][j]);
		}
	}
	DeleteGraph(shot_graphic);
	for(int i = 0; i < MAX_STAGE;i++)
		DeleteGraph(background_graphic[i]);
	for (int i = 0; i < MAX_ENEMY_TYPE; i++) {
		for (int j = 0; j < ENEMY_ANIMETION_NUM; j++) {
			DeleteGraph(enemy_graphic[i][j]);
		}
	}
	for (int i = 0; i < 3; i++) {
		DeleteGraph(weather_graphic[i]);
	}

	for (int i = 0; i < 10; i++) {
		DeleteGraph(font_num_graphic[i]);
	}

	for (int i = 0; i < 4; i++) {
		DeleteGraph(font_timeup_graphic[i]);
	}

	for (int i = 0; i < 1; i++) {
		DeleteGraph(font_length_graphic[i]);
	}

	for (int i = 0; i < 2; i++) {
		DeleteGraph(tomato_effect_graphic[i]);
		DeleteGraph(tomato_item_graphic[i]);
		DeleteGraph(sand_effect_graphic[i]);

	}

	//30日エッグ変更
	for (int i = 0; i < 2; i++) {
		DeleteGraph(font_length_graphic[i]);
	}
	DeleteGraph(speed_meter_graphic);
	DeleteGraph(speed_needle_graphic);
	DeleteGraph(font_tomato_graphic);
	DeleteGraph(shasen_graphic);
}

void LoadSoundAll() {
	stage_bgm[0] = LoadSoundMem("Data/stagebgm0.ogg");
	stage_bgm[1] = LoadSoundMem("Data/stagebgm1.ogg");
	gameover_bgm[0] = LoadSoundMem("Data/gameobera.ogg");
	gameover_bgm[1] = LoadSoundMem("Data/gameobera2.ogg");
	title_bgm = LoadSoundMem("Data/title.ogg");

	warning_se = LoadSoundMem("Data/warning_se.ogg");
	crash_se = LoadSoundMem("Data/crash_se.ogg");
	get_se = LoadSoundMem("Data/get_se.ogg");

	tubure_se = LoadSoundMem("Data/tubure.ogg");
	nageru_se = LoadSoundMem("Data/nageru.ogg");
}

void DeleteSoundAll() {
	for (int i = 0; i < 2; i++) {
		DeleteSoundMem(stage_bgm[i]);
		DeleteSoundMem(gameover_bgm[i]);
	}
}