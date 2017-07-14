#pragma once

#define MAX_TOMATO 255
#define MAX_ENEMY 1
#define STAGE_NUM 2

/*�I�u�W�F�N�g�n*/
typedef struct {
	int graphic[2];			//�v���C���[�摜
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
	int life;				//���C�t
	int life_graphic;		//���C�t�̉摜
	int safetime;			//���G����
	int shot_trigger;		//�V���b�g�̃C���^�[�o��
	int tomato;				//�����g�}�g��
	int speed;
}Player;

typedef struct {
	int life;
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
}Shot;

typedef struct {
	bool is_dead;
	int graphic[2];
	int start_x, start_y;		//�X�^�[�g����|�W�V����
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
	int loopNum;	//���[�v��
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


/*�O���t�B�b�N�n*/
extern int shot_graphic;
extern int tomato_graphic;
extern int speed_meter_graphic;
extern int speed_needle_graphic;

//extern int backbround_graphic[STAGE_NUM];
//extern int karasu_graphic;



/*�umode�v
�Q�[���ɂ́A�^�C�g����ʁA���C����ʁi�Q�[����ʁj�A�Q�[���I�[�o�[��ʂȂǁA���܂��܂ȉ�ʂ�����B
�ϐ��umode�v�Ɍ��݂̏�Ԃ����Ă������ƂŁA��ʂ̐؂�ւ����ł���B
�Ⴆ�΁A�umode�v��0�Ȃ�^�C�g����ʂ�`��A1�Ȃ烁�C����ʂ̕`��A2�Ȃ�Q�[���I�[�o�\��ʂ̕`�������B
�ŏ��̓^�C�g����ʂȂ̂ŁA�����l�Ƃ���0�����Ă����B*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int mode;

/*----------FPS�֘A-----------------*/

extern int mStartTime;      //����J�n����
extern int mCount;          //�J�E���^
extern float mFps;          //fps
extern const int N;	//���ς����T���v����
extern const int FPS;	//�ݒ肵��FPS