#include "Dxlib.h"
#include "Key.h"

int key_z = 0, key_up = 0, key_down = 0, key_left = 0, key_right = 0;

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
}
