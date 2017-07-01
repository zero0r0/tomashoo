#include "DxLib.h"
#include "data.h"
#include "Key.h"

//プレイヤーの初期化の関数
//位置、所持トマトなどを初期化する
void PlayerInit() {
	player.x = 320;
	player.y = 400;
	player.life = 5;
	player.safetime = 0;
	player.tomato = 50;
}

//プレイヤー更新関数
//プレイヤーの動作で追加がある場合ここに書いていく
void PlayerUpdate() {
	


	PlayerMovement();
	//トリガーを-1する
	player.shot_trigger--;
	//Zキーが押されていて、かつトリガーが0以下だったら弾丸を発射する
	if (key_z > 0 && player.shot_trigger <= 0) {
		PlayerShot();
	}
}

//プレイヤーを描画
void PlayerDraw() {
	/*	player_safetimeを2で割った余りを算出し、それが0ならば描画するようにする
	すると、セーフタイム中はプレイヤーが点滅するようになる
	*/
	if (player.safetime % 2 == 0)
		DrawGraph(player.x, player.y, player.graphic, TRUE);
}

///
void PlayerMovement() {
	//キーが押されていたらプレイヤーを移動させる
	if (key_up > 0)		player.y -= 4;
	if (key_down > 0)	player.y += 4;
	if (key_left > 0)	player.x -= 4;
	if (key_right > 0)	player.x += 4;
	//プレイヤーが画面外に出ないようにする
	if (player.x < 0)			player.x = 0;
	if (player.x + 40 > 440)	player.x = 440 - 40;
	if (player.y < 0)			player.y = 0;
	if (player.y + 40 > 480)	player.y = 480 - 40;
}

void PlayerShot() {

	//使用されていない弾丸を探し、見つけたら情報をセットして抜け出す
	for (int i = 0; i < player.tomato; i++) {
		if (shot[i].life == 0) {
			shot[i].life = 1;
			shot[i].x_size = 20;
			shot[i].y_size = 20;
			shot[i].x = player.x + player.x_size / 2 - shot[i].x_size / 2;
			shot[i].y = player.y;

			//トリガーを設定
			player.shot_trigger = 10;
			break;		//ループから脱出
		}
	}
}