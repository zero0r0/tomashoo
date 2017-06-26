#include "Key.h"
#include "DxLib.h"
#include "data.h"


//タイトル時に初期化する処理を書く
void TitleInit() {

}

//タイトル時に更新する処理を書く
void TitleUpdata() {
	if (key_z > 0) {
		mode = MAIN;
		MainGameInit();
	}
}

//タイトルでの描画処理
void TitleDraw() {
	DrawString(0, 0, "とましゅーーーーーーーーー!!", GetColor(255, 255, 255));
}