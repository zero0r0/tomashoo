#include "DxLib.h"
#include "data.h"
#include "Key.h"
#include <math.h>

double total_distance = 0;

void EnemyLoad() {
	FILE *fp;
	char *fname = "Data/enemy.csv";
	int e_type;
	int s_x, s_y;
	int d_x, d_y;
	int time;

	auto e = fopen_s(&fp, fname, "r");
	if (e != 0) {
		printf("ファイル開けない\n");
		return;
	}

	int i = 0;
	int dust;
	//一行目はいらない
	while ((dust = fgetc(fp)) != '\n');
	
	while (i < MAX_ENEMY && (fscanf_s(fp,"%d,%d,%d,%d,%d,%d",&e_type, &s_x,&s_y,&d_x,&d_y, &time)) != EOF)	{
		enemy[i].x = s_x;
		enemy[i].y = s_y;
		enemy[i].move_x = d_x;
		enemy[i].move_y = d_y;
		enemy[i].wait_time = time;
		enemy[i].type = e_type;
		enemy[i].x_size = 48;
		enemy[i].y_size = 48;
		i++;
	}

	fclose(fp);
}

//敵の初期化の関数
void EnemyInit() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].state = 0;
		enemy[i].x = -10;
		enemy[i].y = -10;
		enemy[i].x_size = 0;
		enemy[i].y_size = 0;
		enemy[i].is_dead = false;
		enemy[i].is_appeared = false;
	}
	EnemyLoad();
}

void EnemyUpdate() {
	total_distance += (double)player.speed * (1.0 / mFps);
	SpawnEnemy();
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead && enemy[i].is_appeared) {
			if (enemy[i].type == 5) {
				int x = (int)(sin(2 * PI / 60 * timer) * enemy[i].move_x);
				enemy[i].x += x;
				enemy[i].y += (player.speed + enemy[i].move_y);
				if(enemy[i].y <= 0)
					enemy[i].is_dead = true;
			}
			else {
				enemy[i].y += (player.speed + enemy[i].move_y);
				enemy[i].x += enemy[i].move_x;
				if (enemy[i].y > 480)
					enemy[i].is_dead = true;
			}
		}
		
	}
}

void SpawnEnemy() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].wait_time <= total_distance) {
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
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "%lf", enemy_timer);
}

