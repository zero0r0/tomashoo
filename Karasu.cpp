#include "DxLib.h"
#include "data.h"
#include "Key.h"

//プレイヤーの初期化の関数
//位置、所持トマトなどを初期化する
void KarasuInit() {
	karasu[0].x = 100;
	karasu[0].y = 100;
	karasu[0].x_size = 48;
	karasu[0].y_size = 48;
}


void KarasuUpdate() {

}

void KarasuDraw() {
	DrawGraph(karasu[0].x, karasu[0].y, karasu[0].graphic[0], TRUE);
}
