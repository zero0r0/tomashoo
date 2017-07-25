#pragma once

#define MAX_TOMATO 255
#define MAX_ITEM 5
#define MAX_ENEMY 100
#define MAX_ENEMY_TYPE 7
#define MAX_STAGE 4
#define CHANGE_BACKGROUND_BY_LOOP_NUM 3
#define ENEMY_ANIMETION_NUM 2	//�G�̃A�j���[�V�����̉摜��
#define PI    3.1415926535897932384626433832795f

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
	int anim_count;			//count����萔���܂�����++����
	int count;				//�}�C�t���[���J�E���g���Ă���
	int r;
}Player;

typedef struct {
	int life;	
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
	int r;
}Shot;

typedef struct {
	bool is_appeared;		//�o���������ǂ���
	bool is_dead;			//���񂾁A��ʊO��
	//int graphic[2];
	int state;				//�ǂ̃A�j���[�V�����摜�̃X�e�[�g��
	int count;
	int x, y;					
	int x_size, y_size;
//	int wait_time;			//�o������
	int type;				//1:�J���X�A2:�͂��сA3:�C�m�V�V 4.���s,5,�s��
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
	int loopNum;			//���[�v��
}Background;

typedef struct{
	int x, y;
	int state;	//�A�j���[�V�����̏��
	int count;	//�A�j���[�V�������̃J�E���g
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
void SpawnEnemy(int);
void SpawnEffect(int, int);

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
extern Background background[MAX_STAGE];


/*�O���t�B�b�N�n*/
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
extern int tomato_effect_graphic;
extern int sand_effect_graphic[2];

/*�uscene�v
�Q�[���ɂ́A�^�C�g����ʁA���C����ʁi�Q�[����ʁj�A�Q�[���I�[�o�[��ʂȂǁA���܂��܂ȉ�ʂ�����B
�ϐ��uscene�v�Ɍ��݂̏�Ԃ����Ă������ƂŁA��ʂ̐؂�ւ����ł���B
�Ⴆ�΁A�uscene�v��0�Ȃ�^�C�g����ʂ�`��A1�Ȃ烁�C����ʂ̕`��A2�Ȃ�Q�[���I�[�o�\��ʂ̕`�������B
�ŏ��̓^�C�g����ʂȂ̂ŁA�����l�Ƃ���0�����Ă����B*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int scene;

extern double total_distance;
extern double timer;

/*----------FPS�֘A-----------------*/

extern int mStartTime;      //����J�n����
extern int mCount;          //�J�E���^
extern float mFps;          //fps
extern const int N;	//���ς����T���v����
extern const int FPS;	//�ݒ肵��FPS

extern bool is_clear;
extern bool last_stage;
