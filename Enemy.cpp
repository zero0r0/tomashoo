#include "DxLib.h"
#include "data.h"
#include "Key.h"
#include <math.h>


int total_distance = 0;
int enemy_timer = 0;
Effect sand_effect[EFFECT_NUM];
bool is_first_kill = true;

//敵の初期化の関数
void EnemyInit() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		enemy[i].state = 0;
		enemy[i].x = -100;
		enemy[i].y = -100;
		enemy[i].move_x = 0;
		enemy[i].move_y = 0;
		enemy[i].x_size = 48;
		enemy[i].y_size = 48;
		enemy[i].type = 0;
		enemy[i].is_dead = true;
		//enemy[i].is_appeared = false;
		enemy[i].r = 15;
	}

	//エフェクト初期化
	for (int i = 0; i < EFFECT_NUM; i++) {
		sand_effect[i].x = -10;
		sand_effect[i].y = -10;
		sand_effect[i].count = 0;
		sand_effect[i].is_used = false;
		sand_effect[i].state = 0;
	}

	enemy_timer = 0;
	is_first_kill = true;
	//EnemyLoad();
}

//敵の更新関数
//出現時のエフェクト処理も含む
void EnemyUpdate() {
	bool is_spawn = false;
	int interval = 60 * ((background[0].now_stage < 2) ? 1 : 2);

	//total_distance += (double)player.speed * (1.0 / mFps);
	enemy_timer += player.speed;
	

	//一定時間で敵を出現させる
	if (enemy_timer > interval && !(30 <= length && length <= 37 ) && !(65 <= length && length <= 70))
		is_spawn = true;
	else
		is_spawn = false;
	
	if (length <= 6 && is_spawn && is_first_kill) {
		is_spawn = false;
		enemy[0].x = 700;
		enemy[0].y = background[0].y + 1060;
		enemy[0].move_x = -10;
		enemy[0].move_y = 0;
		enemy[0].type = 9;
		enemy[0].is_dead = false;
		enemy_timer = 0;

		enemy[1].x = -300;
		enemy[1].y = background[0].y + 930;
		enemy[1].move_x = 10;
		enemy[1].move_y = 0;
		enemy[1].type = 10;
		enemy[1].is_dead = false;
		enemy_timer = 0;

		is_first_kill = false;
	}

	for (int i = 0; i < MAX_ENEMY; i++) {
		if (enemy[i].is_dead) {
			if (is_spawn) {
				SpawnEnemy(i,background[1].now_stage,0);
				is_spawn = false;
				enemy_timer = 0;
			}
		}
		else{
			enemy[i].y += player.speed;
			if (enemy[i].y > BEGINING_MOVE_Y) {
				enemy[i].x += enemy[i].move_x;
				enemy[i].y += enemy[i].move_y;
				//if (enemy[i].type == 3) {
				//	enemy[i].x += sin(PI * 2 / 60 * timer) * enemy[i].move_x;
				//}else
			}
			if (enemy[i].y > 500) {
				enemy[i].is_dead = true;
			}
		}

		//アニメーション処理
		if (enemy[i].count > 10) {
			enemy[i].state++;
			enemy[i].count = 0;
		}
		else {
			enemy[i].count++;
		}
	}

	//エフェクトの処理
	for (int i = 0; i < EFFECT_NUM; i++) {
		if (sand_effect[i].is_used) {
			if (sand_effect[i].count > 10) {
				sand_effect[i].state++;
				sand_effect[i].count = 0;
			}
			else
				sand_effect[i].count++;

			if (sand_effect[i].state > 4) {
				sand_effect[i].count = 0;
				sand_effect[i].is_used = false;
				sand_effect[i].x = -10;
				sand_effect[i].y = -10;
				sand_effect[i].state = 0;
			}
		}
	}
}

//敵出現時の関数
void SpawnEnemy(int n, int stage, int enemy_num) {
	int type = 0;
	int x = 0, y = 0;// -480 / ENEMY_SPAWN_NUM;
	int m_x = 0, m_y = 0;
	int rand_spawn = GetRand(2);

	if (last_stage)
		return;

	//ステージで出てくる敵の種類を決める
	switch (stage)
	{
		case 0:
			type = 0;
			break;
		case 1:
			type = GetRand(2);
			break;
		case 2:
			type = 4 + GetRand(4);
			break;
		//default:
		//	return;
		//	break;
	}

	//敵によって出現方法や移動量を変える
	switch (type)
	{
		//カラス
		case 0:
			if (rand_spawn == 0) {
				x = GetRand(640);
				y = -GetRand(480);
			}
			else if (rand_spawn == 1) {
				x = -GetRand(50);
				y = GetRand(480);
			}
			else {
				x = 640 + GetRand(50);
				y = GetRand(480);
			}

			if (x < 360)
				m_x = 2 + GetRand(4);
			else
				m_x = (-2) * (1 + GetRand(4));
			m_y = GetRand(4);
			break;
		//ハクビシン
		case 1:
			x = GetRand(640);
			y = -GetRand(480);
			break;
		//イノシシ
		case 2:
			x = GetRand(640);
			y = -GetRand(480);
			m_y = GetRand(10);
			SpawnEffect(x,5);
			break;
		case 3:
			x = 100 + GetRand(220);
			y = 480;
			m_x = 2 + GetRand(5);
			m_y = -6;
			break;
		//歩行者１
		case 4:
			x = 100;
			y = -40;
			break;
		case 5:
			x = 100;
			y = -40;
			m_x = GetRand(2);
			m_y = 0;
			break;
		case 6:
			x = 520;
			y = -40;
			m_x = -GetRand(2);
			m_y = 0;
			break;
		//とラック
		case 7:
			x = 120;
			y = 480;
			m_x = 0;
			m_y = -5;
			break;
		case 8:
			x = 350;
			y = -50;
			m_x = 0;
			m_y = 5;
			break;
		default:
			break;
	}
	//y = y * enemy_num;

	enemy[n].x = x;
	enemy[n].y = y;
	enemy[n].move_x = m_x;
	enemy[n].move_y = m_y;
	enemy[n].type = type;
	enemy[n].is_dead = false;
}

void SpawnEffect(int x, int y) {
	for (int i = 0; i < EFFECT_NUM; i++) {
		if (!sand_effect[i].is_used) {
			sand_effect[i].x = x;
			sand_effect[i].y = y;
			sand_effect[i].count = 0;
			sand_effect[i].state = 0;
			sand_effect[i].is_used = true;
			break;
		}
	}
}

void EnemyDraw() {
	for (int i = 0; i < MAX_ENEMY; i++) {
		if (!enemy[i].is_dead) {
			DrawGraph(enemy[i].x, enemy[i].y, enemy_graphic[enemy[i].type][enemy[i].state % 2], TRUE); //22日エッグ変更
			//DrawCircle(enemy[i].x + 24, enemy[i].y + 24, enemy[i].r, GetColor(255, 255, 255), true);
		}
	}

	//エフェクト描画
	for (int i = 0; i < EFFECT_NUM; i++) {
		if (sand_effect[i].is_used) {
			DrawGraph(sand_effect[i].x, sand_effect[i].y, sand_effect_graphic[sand_effect[i].state%2],true);
		}
	}
	//DrawFormatString(400, 420, GetColor(255, 255, 255), "stage : %d", background[0].now_stage);
	//DrawFormatString(400, 440, GetColor(255, 255, 255), "%d", en);
}
