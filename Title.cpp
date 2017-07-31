#include "Key.h"
#include "DxLib.h"
#include "data.h"


//タイトル時に初期化する処理を書く
void TitleInit() {

}

//タイトル時に更新する処理を書く
void TitleUpdata() {
	if (key_z == 1) {
		MainGameInit();
		scene = MAIN;
	}

}

//タイトルでの描画処理
void TitleDraw() {
	DrawString(0, 0, "とましゅーーーーーーーーー!!", GetColor(255, 255, 255));
	DrawString(100, 100, "push Z key", GetColor(255, 255, 255));
	//DrawGraph(0, 0, background_graphic[MAX_STAGE-1], true);
}