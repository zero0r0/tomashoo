#pragma once

#define MAX_TOMATO 255

/*�I�u�W�F�N�g�n*/
typedef struct {
	int graphic;			//�v���C���[�摜
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
	int life;				//���C�t
	int life_graphic;		//���C�t�̉摜
	int safetime;			//���G����
	int shot_trigger;		//�V���b�g�̃C���^�[�o��
	int tomato;				//�����g�}�g��
}Player;

typedef struct {
	int life;
	int x, y;				//xy���W
	int x_size, y_size;		//x.y�傫��
}Shot;

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerMovement();
void PlayerShot();

void TitleInit();
void TitleUpdata();
void TitleDraw();

void MainGameInit();
void MainGameUpdate();
void MainGameDraw();


extern Player player;
extern Shot shot[MAX_TOMATO];

/*�O���t�B�b�N�n*/
extern int shot_graphic;
extern int tomato_grahic;

/*�umode�v
�Q�[���ɂ́A�^�C�g����ʁA���C����ʁi�Q�[����ʁj�A�Q�[���I�[�o�[��ʂȂǁA���܂��܂ȉ�ʂ�����B
�ϐ��umode�v�Ɍ��݂̏�Ԃ����Ă������ƂŁA��ʂ̐؂�ւ����ł���B
�Ⴆ�΁A�umode�v��0�Ȃ�^�C�g����ʂ�`��A1�Ȃ烁�C����ʂ̕`��A2�Ȃ�Q�[���I�[�o�\��ʂ̕`�������B
�ŏ��̓^�C�g����ʂȂ̂ŁA�����l�Ƃ���0�����Ă����B*/
extern int const TITLE;
extern int const MAIN;
extern int const GAMEOVER;
extern int mode;
