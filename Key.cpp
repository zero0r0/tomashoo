#include "Dxlib.h"
#include "Key.h"

int key_z = 0, key_up = 0, key_down = 0, key_left = 0, key_right = 0;
int key_a = 0, key_s = 0, key_w, key_d;

void KeyUpdate() {
	//�L�[�̓��͏󋵂��`�F�b�N����
	//Z�L�[��������Ă�����ukey_z�v�����Z�A�����łȂ��Ȃ�0����
	if (CheckHitKey(KEY_INPUT_Z) == 1) key_z++;
	else key_z = 0;
	if (CheckHitKey(KEY_INPUT_UP) == 1) key_up++;
	else key_up = 0;
	if (CheckHitKey(KEY_INPUT_DOWN) == 1) key_down++;
	else key_down = 0;
	if (CheckHitKey(KEY_INPUT_LEFT) == 1) key_left++;
	else key_left = 0;
	if (CheckHitKey(KEY_INPUT_RIGHT) == 1) key_right++;
	else key_right = 0;
	if (CheckHitKey(KEY_INPUT_A) == 1) key_a++;
	else key_a = 0;
	if (CheckHitKey(KEY_INPUT_S) == 1) key_s++;
	else key_s = 0;
	if (CheckHitKey(KEY_INPUT_W) == 1) key_w++;
	else key_w = 0;
	if (CheckHitKey(KEY_INPUT_D) == 1) key_d++;
	else key_d = 0;
}
