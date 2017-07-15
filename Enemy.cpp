#include "DxLib.h"
#include "data.h"
#include "Key.h"

double enemy_timer = 0;

void EnemyLoad() {
	FILE *fp;
	char *fname = "Data/enemy.csv";
	int e_type;
	int s_x, s_y;
	int d_x, d_y;
	int time;

	auto e = fopen_s(&fp, fname, "r");
	if (e != 0) {
		printf("�t�@�C���J���Ȃ�\n");
		return;
	}

	int i = 0;
	int dust;
	//��s�ڂ͂���Ȃ�
	while ((dust = fgetc(fp)) != '\n');
	
	while (i < MAX_ENEMY && (fscanf_s(fp,"%d,%d,%d,%d,%d,%d",&e_type, &s_x,&s_y,&d_x,&d_y, &time)) != EOF)	{
		enemy[i].x = s_x;
		enemy[i].y = s_y;
		enemy[i].move_direction_x = d_x;
		enemy[i].move_direction_y = d_y;
		enemy[i].wait_time = time;
		enemy[i].type = e_type;
		i++;
	}

	fclose(fp);
}

//�G�̏������̊֐�
void EnemyInit() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].state = 0;
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].x_size = 48;
		enemy[i].y_size = 48;
		enemy[i].is_dead = false;
		enemy[i].is_appeared = false;
	}
	enemy_timer = 0;
	EnemyLoad();
}

void EnemyUpdate() {
	enemy_timer += (double)player.speed * (1.0 / mFps);
	SpawnEnemy();
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead && enemy[i].is_appeared) {
			enemy[i].y += (player.speed + enemy[i].move_direction_y);
			enemy[i].x += enemy[i].move_direction_x;
		}
		if (enemy[i].y > 480)
			enemy[i].is_dead = true;
	}
}

void SpawnEnemy() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].wait_time <= enemy_timer) {
			enemy[i].is_appeared = true;
		}
	}
}

void EnemyDraw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead && enemy[i].is_appeared) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_graphic[enemy[i].type][enemy[i].state], TRUE);
		}
	}
	DrawFormatString(0, 20, GetColor(255, 255, 255), "%lf", enemy_timer);
}

