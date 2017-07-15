#include "DxLib.h"
#include "data.h"
#include "Key.h"

int enemy_count = 0;
double enemy_timer = 0;

void EnemyLoad() {
	FILE *fp;
	char *fname = "Data/enemy.csv";
	int e_type;
	int s_x, s_y;
	int d_x, d_y;
	int speed;
	double time;

	auto e = fopen_s(&fp, fname, "r");
	if (e != 0) {
		printf("ファイル開けない\n");
		return;
	}

	int i = 0;

	while (i < MAX_ENEMY && (fscanf_s(fp,"%d,%d,%d,%d,%d,%d,%lf",&e_type, &s_x,&s_y,&d_x,&d_y,&speed, &time)) != EOF)	{
		enemy[i].x = s_x;
		enemy[i].y = s_y;
		enemy[i].move_direction_x = d_x;
		enemy[i].move_direction_y = d_y;
		enemy[i].wait_time = time;
		enemy[i].type = e_type;
		enemy[i].speed = speed;
		i++;
	}

	fclose(fp);
}

//敵の初期化の関数
void EnemyInit() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].state = 0;
		enemy[i].x = 0;
		enemy[i].y = 0;
		enemy[i].x_size = 48;
		enemy[i].y_size = 48;
		enemy[i].is_dead = true;
	}
	enemy_count = 0;
	enemy_timer = 0;
	EnemyLoad();
}

void EnemyUpdate() {
	enemy_timer += player.speed * (1 / mFps);
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead) {
			enemy[i].y += (player.speed + enemy[i].speed + enemy[i].move_direction_y);
			enemy[i].x += enemy[i].speed * enemy[i].move_direction_x;
		}
	}
	SpawnEnemy();

}

void SpawnEnemy() {
	if (enemy[enemy_count].wait_time >= timer && enemy_count < MAX_ENEMY) {
		enemy[enemy_count].is_dead = false;
		enemy_count++;
	}
}

void EnemyDraw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead) {
			switch (enemy[i].type)
			{
			case 0:
				DrawGraph(enemy[i].x, enemy[i].y, karasu_graphic[enemy[i].state], TRUE);
				break;
			default:
				break;
			}
		}
	}
}

