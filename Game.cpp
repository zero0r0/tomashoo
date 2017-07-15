#include "DxLib.h"
#include "Key.h"
#include "data.h"

#define WINDOW_XSIZE 640
#define WINDOW_YSIZE 480


void TestMessage();		//�֐��̃v���g�^�C�v�錾
void LoadGraphicAll();
void DeleteGraphicAll();


Player player;
Shot shot[MAX_TOMATO];
Item item[MAX_TOMATO];
Enemy enemy[MAX_ENEMY];
Background background[MAX_STAGE];

int mode;
int const TITLE = 0;
int const MAIN = 1;
int const GAMEOVER = 2;

//�O���t�B�b�N�n
int shot_graphic;
int tomato_graphic;
int speed_meter_graphic;
int speed_needle_graphic;
int background_graphic[MAX_STAGE];
int enemy_graphic[MAX_ENEMY_TYPE][ENEMY_ANIMETION_NUM];

/*----------FPS�֘A-----------------*/

int mStartTime;      //����J�n����
int mCount;          //�J�E���^
float mFps;          //fps
const int N = 60;	//���ς����T���v����
const int FPS = 60;	//�ݒ肵��FPS

bool Update() {
	if (mCount == 0) { //1�t���[���ڂȂ玞�����L��
		mStartTime = GetNowCount();
	}
	if (mCount == N) { //60�t���[���ڂȂ畽�ς��v�Z����
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
	int tookTime = GetNowCount() - mStartTime;	//������������
	int waitTime = mCount * 1000 / FPS - tookTime;	//�҂ׂ�����
	if (waitTime > 0) {
		Sleep(waitTime);	//�ҋ@
	}
}

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hp, LPSTR lpC, int nC) {

	/*----------------����{�I�Ȑݒ�----------------------
	��{�I�Ȑݒ�͂ǂ̃Q�[���ł��قڃR�s�y�Ȃ̂ŁA
	�Ӗ��͂��܂�C�ɂ��Ȃ��Ă������[
	*/
	ChangeWindowMode(TRUE);					//�E�B���h�E���[�h�ɂ���
	SetMainWindowText("�e�X�g�Q�[��");		//�E�B���h�E�̃^�C�g����ύX����
	SetWindowSizeChangeEnableFlag(FALSE);
	SetGraphMode(WINDOW_XSIZE, WINDOW_YSIZE, 32);				//�E�B���h�E�̃T�C�Y��640x480�ɂ���
	SetWindowSizeExtendRate(1);

	if (DxLib_Init() == -1) return -1;		//Dx���C�u����������������
	SetOutApplicationLogValidFlag(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);			//�`��Ώۂ𗠉�ʂɂ���

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);  //�t�H���g�̐ݒ�
	SetFontSize(18);

	/*----------------����{�I�Ȑݒ�----------------------*/

	//�Q�[���̏�񂢂낢��
	int score;
	int max_score = 0;

	FILE* rf;
	//�t�@�C����ǂݍ���
	fopen_s(&rf, "Data/max_score.txt", "r");
	//�t�@�C���̓ǂݍ��݂ɐ���������A��������l��ǂݍ���
	if (rf != NULL) {
		fread(&max_score, sizeof(int), 1, rf);
		fclose(rf);	//�t�@�C�������
	}
	
	LoadGraphicAll();

	mode = TITLE;
	TitleInit();

	//���C�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		Update();
		ClearDrawScreen();
		KeyUpdate();
		//--------------�Q�[���̏���������-----------------
		//�ϐ��umode�v��0�Ȃ�΁A�^�C�g����ʂ̏���������
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
	LoadDivGraph("Data/en01.png", 2, 2, 1, 48, 48, enemy_graphic[0]);
	LoadDivGraph("Data/en02.png", 2, 2, 1, 48, 48, enemy_graphic[1]);
	LoadDivGraph("Data/en03.png", 2, 2, 1, 48, 48, enemy_graphic[2]);
	LoadDivGraph("Data/en04.png", 2, 2, 1, 48, 48, enemy_graphic[3]);
//	LoadDivGraph("Data/en05.png", 2, 2, 1, 48, 48, enemy_graphic[4]);

	player.life_graphic = LoadGraph("Data/life.bmp");
	tomato_graphic = LoadGraph("Data/bl01.png");
	background_graphic[0] = LoadGraph("Data/inaka.png");
	background_graphic[1] = LoadGraph("Data/hatake.png");
	speed_meter_graphic = LoadGraph("Data/speed_meter.png");
	speed_needle_graphic = LoadGraph("Data/speed_needle.png");
}

void DeleteGraphicAll() {
	DeleteGraph(player.graphic[0]);
	DeleteGraph(player.graphic[1]);
	DeleteGraph(player.life_graphic);
	DeleteGraph(tomato_graphic);
	for(int i = 0; i < MAX_STAGE;i++)
		DeleteGraph(background_graphic[i]);
	for (int i = 0; i < MAX_ENEMY_TYPE; i++) {
		for (int j = 0; j < ENEMY_ANIMETION_NUM; j++) {
			DeleteGraph(enemy_graphic[i][j]);
		}
	}
	DeleteGraph(speed_meter_graphic);
	DeleteGraph(speed_needle_graphic);
}

void TestMessage() {
	DrawFormatString(0, 0, GetColor(255, 255, 255), "�ϐ� mode �̒l�� %d �ł�", mode);
}