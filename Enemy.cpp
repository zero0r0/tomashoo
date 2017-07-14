#include "DxLib.h"
#include "data.h"
#include "Key.h"

void EnemyLoad() {
	FILE *fp;
	char *fname = "Data/enemy.csv";
	int e_type;
	int s_x, s_y;
	int x, y;
	int speed;
	double time;

	fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("�t�@�C���J���Ȃ�\n");
		return;
	}

	int i = 0;
	while ((fscanf(fp,"%d,%d,%d,%d,%d,%d,%lf",&e_type, &s_x,&s_y,&x,&y,&time,&speed)) != EOF)	{
					
	}

}

//�v���C���[�̏������̊֐�
//�ʒu�A�����g�}�g�Ȃǂ�����������
void EnemyInit() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].x_size = 48;
		enemy[i].y_size = 48;
		enemy[i].is_dead = false;	//��ʁ����̓g�}�g�����������玀�񂾂Ƃ݂Ȃ�
	}
}

void EnemyUpdate() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead) {
			enemy[i].y += player.speed;
		}
	}
}

void EnemyDraw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[0].is_dead) {
			DrawGraph(enemy[0].x, enemy[0].y, enemy[0].graphic[0], TRUE);
		}
	}
}
