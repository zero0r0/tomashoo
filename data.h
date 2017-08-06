#pragma once

#define MAX_TOMATO 255
#define MAX_ITEM 8
#define MAX_ENEMY 125
#define ENEMY_SPAWN_NUM 5
#define MAX_ENEMY_TYPE 11
#define MAX_STAGE 4
#define CHANGE_BACKGROUND_BY_LOOP_NUM 3
#define ENEMY_ANIMETION_NUM 2	//�G�̃A�j���[�V�����̉摜��
#define PI    3.1415926535897932384626433832795f
#define EFFECT_NUM 25
#define BEGINING_MOVE_Y -25
#define TIME_LIMIT 60

/*�I�u�W�F�N�g�n*/
typedef struct {
	int graphic[2][2];		//�v���C���[�摜
	int x, y;				//xy���W
	int width_speed;
	int x_size, y_size;		//x.y�傫��
	int safetime;			//���G����
	int shot_trigger;		//�V���b�g�̃C���^�[�o��
	int tomato;				//�����g�}�g��
	int speed;
	int anim_count;			//count����萔���܂�����++����
	int count;				//�}�C�t���[���J�E���g���Ă���
	int r;
	//25���G�b�O�ύX
	int time;
	int fleam_count;
}Player;

typedef struct {
	//int life;	
	bool is_active;
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
	int r;
}Shot;

typedef struct {
	//bool is_appeared;		//�o���������ǂ���
	bool is_dead;			//���񂾁A��ʊO��
	int state;				//�ǂ̃A�j���[�V�����摜�̃X�e�[�g��
	int count;
	int x, y;					
	int x_size, y_size;
	int type;				//1:�J���X�A2:�͂��сA3:�C�m�V�V 4.���s,5,�s��
	int move_x;				
	int move_y;				
	int r;
}Enemy;

typedef struct {
	int x, y;
	int x_size, y_size;
	int r;
	int state;	//�A�j���[�V�����̏��
	int count;	//�A�j���[�V�������̃J�E���g
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
void TitleExit();
bool WindowOpen();
bool WindowClose();

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



/*�O���t�B�b�N�n*/
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

extern int titlelogo_graphic[3];
extern int title_botton_graphic[3];
extern int title_tomato_graphic[2];
extern int title_conbea_graphic;
extern int title_pushed_tomato_graphic;
extern int title_description_window_graphic[6];
extern int title_desctiption_graphic[3];

//�T�E���h�n
extern int stage_bgm[2];
extern int gameover_bgm[2];
extern int title_bgm;

extern int crash_se;
extern int warning_se;
extern int get_se;
extern int tubure_se;
extern int nageru_se;

/*�uscene�v
�Q�[���ɂ́A�^�C�g����ʁA���C����ʁi�Q�[����ʁj�A�Q�[���I�[�o�[��ʂȂǁA���܂��܂ȉ�ʂ�����B
�ϐ��uscene�v�Ɍ��݂̏�Ԃ����Ă������ƂŁA��ʂ̐؂�ւ����ł���B
�Ⴆ�΁A�uscene�v��0�Ȃ�^�C�g����ʂ�`��A1�Ȃ烁�C����ʂ̕`��A2�Ȃ�Q�[���I�[�o�\��ʂ̕`�������B
�ŏ��̓^�C�g����ʂȂ̂ŁA�����l�Ƃ���0�����Ă����B*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int const CLEAR;
extern int scene;
extern bool is_exit;

extern int total_distance;
//30���G�b�O�ύX
extern int length;     //����
extern double timer;

/*----------FPS�֘A-----------------*/

extern int mStartTime;      //����J�n����
extern int mCount;          //�J�E���^
extern float mFps;          //fps
extern const int N;	//���ς����T���v����
extern const int FPS;	//�ݒ肵��FPS

extern bool is_clear;
extern bool last_stage;
extern int now_wave;

//font�֘A
extern int FontHandle[3];