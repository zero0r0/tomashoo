#pragma once

#define MAX_TOMATO 255
#define MAX_ENEMY 25
#define MAX_ENEMY_TYPE 5
#define MAX_STAGE 2
#define CHANGE_BACKGROUND_BY_LOOP_NUM 5
#define ENEMY_ANIMETION_NUM 2	//�G�̃A�j���[�V�����̉摜��

/*�I�u�W�F�N�g�n*/
typedef struct {
	int graphic[2];			//�v���C���[�摜
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
	int life;				//���C
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
	//int graphic[2];
	int state;					//�ǂ̃A�j���[�V�����摜�̃X�e�[�g��
	int x, y;					
	int x_size, y_size;
	int speed;
	double wait_time;			//�o������
	int type;
	int move_direction_x;
	int move_direction_y;
}Enemy;

typedef struct {
	int x, y;
	int x_size, y_size;
}Item;

typedef struct {
	int x, y;
	int x_size, y_size;
	int now_stage;
	int loopNum;			//���[�v��
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


/*�O���t�B�b�N�n*/
extern int shot_graphic;
extern int tomato_graphic;
extern int speed_meter_graphic;
extern int speed_needle_graphic;
extern int background_graphic[MAX_STAGE];
extern int enemy_graphic[MAX_ENEMY_TYPE][ENEMY_ANIMETION_NUM];



/*�umode�v
�Q�[���ɂ́A�^�C�g����ʁA���C����ʁi�Q�[����ʁj�A�Q�[���I�[�o�[��ʂȂǁA���܂��܂ȉ�ʂ�����B
�ϐ��umode�v�Ɍ��݂̏�Ԃ����Ă������ƂŁA��ʂ̐؂�ւ����ł���B
�Ⴆ�΁A�umode�v��0�Ȃ�^�C�g����ʂ�`��A1�Ȃ烁�C����ʂ̕`��A2�Ȃ�Q�[���I�[�o�\��ʂ̕`�������B
�ŏ��̓^�C�g����ʂȂ̂ŁA�����l�Ƃ���0�����Ă����B*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int mode;

extern double timer;

/*----------FPS�֘A-----------------*/

extern int mStartTime;      //����J�n����
extern int mCount;          //�J�E���^
extern float mFps;          //fps
extern const int N;	//���ς����T���v����
extern const int FPS;	//�ݒ肵��FPS