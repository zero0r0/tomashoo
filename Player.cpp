#include "DxLib.h"
#include "data.h"
#include "Key.h"

//30日エッグ変更
#define MAX_SPEED 10.0
//30日エッグ変更
int length = 0;

//プレイヤーの初期化の関数
//位置、所持トマトなどを初期化する
void PlayerInit() {
	player.x = 320;
	player.y = 320;
	player.x_size = 48;
	player.y_size = 48;
	player.safetime = 10;
	player.shot_trigger = 10;
	player.tomato = 50;
	player.speed = 1;
	player.count = 0;
	player.anim_count = 0;
	player.r = 10;
	//25日エッグ変更
	player.time = TIME_LIMIT;
	player.fleam_count = 0;
	player.width_speed = 4;
}

//プレイヤー更新関数
//プレイヤーの動作で追加がある場合ここに書いていく
void PlayerUpdate() {
	
	//アニメーション
	if (player.count > 10) {
		player.anim_count++;
		player.count = 0;
	}
	else {
		player.count++;
	}

	//25日エッグ変更
	if (player.fleam_count % 60 == 0 && !is_clear
		) {
		player.time--;
	}
	player.fleam_count++;

	PlayerMovement();
	PlayerCollision();
	//トリガーを-1する
	player.shot_trigger--;
	//Zキーが押されていて、かつトリガーが0以下だったら弾丸を発射する
	if (key_z > 0 && player.shot_trigger <= 0 && player.tomato > 0) {
		PlayerShot();
		player.tomato -= 1;
	}
	if (key_up == 1 && player.speed < MAX_SPEED) {
		PlayerSpeedUp();
	}
	else if(key_down == 1 && player.speed >= 1){
		PlayerSpeedDown();
	}
	//DrawFormatString(300, 300, , "life の値は %d です", player.life);
}

//プレイヤーを描画
void PlayerDraw() {
	/*	player_safetimeを2で割った余りを算出し、それが0ならば描画するようにする
	すると、セーフタイム中はプレイヤーが点滅するようになる
	*/
	//if (player.safetime % 2 == 0)
	//	DrawGraph(player.x, player.y, player.graphic[player.anim_count%2], TRUE);
	if (player.safetime % 2 == 0) {
		//30日エッグ変更
		if (key_z > 0 && player.tomato > 0)
			DrawGraph(player.x, player.y, player.graphic[1][player.anim_count % 2], TRUE);
		else DrawGraph(player.x, player.y, player.graphic[0][player.anim_count % 2], TRUE);
		//
	}
	DrawGraph(150, 440, speed_meter_graphic, TRUE);
	DrawRotaGraph2(335, 490, 20, 40, 1.0, (PI * (double)(player.speed / MAX_SPEED) - PI/2), speed_needle_graphic, TRUE);
	DrawGraph(100, 400, font_num_graphic[player.tomato %10], true);
	DrawGraph(65, 400, font_num_graphic[(player.tomato /10 ) %10], true);
	DrawGraph(30, 400, font_num_graphic[(player.tomato /100 ) %10], true);
	DrawGraph(140, 400, shasen_graphic, true);
	//30日エッグ変更
	DrawGraph(230, 400, font_num_graphic[0], true);
	DrawGraph(195, 400, font_num_graphic[5], true);
	DrawGraph(160, 400, font_num_graphic[0], true);
	DrawGraph(30, 365, font_tomato_graphic, true);

	//プレイヤーの距離の描画
	//25日エッグ変更
	DrawGraph(450, 355, font_timeup_graphic[0], true);
	DrawGraph(550, 355, font_timeup_graphic[1], true);
	DrawGraph(450, 420, font_timeup_graphic[2], true);
	DrawGraph(510, 400, font_num_graphic[player.time % 10], true);
	DrawGraph(475, 400, font_num_graphic[(player.time / 10) % 10], true);
	DrawGraph(560, 420, font_timeup_graphic[3], true);
	DrawGraph(15, 10, font_length_graphic[0], true);
	//DrawGraph(85, 20, font_num_graphic[(320 - total_distance) / 10 % 10], true);
	//DrawGraph(120, 20, font_num_graphic[(320 - total_distance) % 10], true);
	//DrawCircle(player.x + 24, player.y + 24, player.r, GetColor(255, 255, 255), true);
	DrawGraph(85, 20, font_num_graphic[length / 100 % 10], true);
	DrawGraph(120, 20, font_num_graphic[length / 10 % 10], true);
	DrawGraph(155, 20, font_num_graphic[length % 10], true);
	DrawGraph(200, 50, font_length_graphic[1], true);
}

///
void PlayerMovement() {
	if (player.tomato < 30) {
		player.width_speed = 6;
	}
	else if (30 <= player.tomato && player.tomato <= 60) {
		player.width_speed = 4;
	}
	else {
		player.width_speed = 2;
	}

	if (key_left > 0)	player.x -= player.width_speed;
	if (key_right > 0)	player.x += player.width_speed;
	//プレイヤーが画面外に出ないようにする
	if (player.x < 0)			player.x = 0;
	if (player.x  > 640)	player.x = 640;
	if (player.y < 0)			player.y = 0;
	if (player.y  > 480)	player.y = 480;
}

void PlayerShot() {

	//使用されていない弾丸を探し、見つけたら情報をセットして抜け出す
	for (int i = 0; i < player.tomato; i++) {
		if (!shot[i].is_active) {
			shot[i].is_active = true;
			shot[i].x_size = 48;
			shot[i].y_size = 48;
			shot[i].x = player.x + player.x_size / 2 - shot[i].x_size / 2;
			//27日エッグ変更
			shot[i].y = player.y - 30;
			//トリガーを設定
			player.shot_trigger = 10;
			break;		//ループから脱出
		}
	}
}

void PlayerCollision() {
	for (int i = 0; i < MAX_TOMATO; i++) {
		if ((player.x + player.x_size / 2 - (item[i].x + item[i].x_size / 2))* (player.x + player.x_size / 2 - (item[i].x + item[i].x_size / 2)) + (player.y + player.y_size / 2 - (item[i].y + item[i].y_size / 2))* (player.y + player.y_size / 2 - (item[i].y + item[i].y_size / 2)) <= (player.r + item[i].r)*(player.r + item[i].r)) {
			player.tomato += 4 * (weather_number+1);
			item[i].y = -100;
			item[i].x = -100;
		}
	}
	
	if (player.safetime > 0)
		player.safetime--;
	else {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if ((player.x + player.x_size / 2 - (enemy[i].x + enemy[i].x_size / 2))*(player.x + player.x_size / 2 - (enemy[i].x + enemy[i].x_size / 2)) + (player.y + player.y_size / 2 - (enemy[i].y + enemy[i].y_size / 2))*(player.y + player.y_size / 2 - (enemy[i].y + enemy[i].y_size / 2)) <= (player.r + enemy[i].r)*(player.r + enemy[i].r)) { //22日エッグ変更
				Damage(enemy[i].type);
				player.safetime = 60;
				/*if (enemy[i].type == 2 || 4 <= enemy[i].type) {
					GameoverInit(3);
				}
				*/
			}
		}
	}
}

void Damage(int type) {
	int damage=0;
	switch (type)
	{
		case 0:
			damage = 1 + GetRand(2);
			break;
		case 1:
			damage = 1 + GetRand(4);
			player.speed = (0 < player.speed-2) ? player.speed-2 : 1;
			break;
		default:
			GameoverInit(3);
			return;
			break;
	}
	damage = player.tomato - damage;
	player.tomato = (0 < damage) ? damage : 0;
}

void PlayerSpeedUp() {
	player.speed += 1;
}

void PlayerSpeedDown() {
	player.speed -= 1;
}