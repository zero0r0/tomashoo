#include "DxLib.h"
#include "data.h"
#include "Key.h"

#define PI    3.1415926535897932384626433832795f

//�v���C���[�̏������̊֐�
//�ʒu�A�����g�}�g�Ȃǂ�����������
void PlayerInit() {
	player.x = 320;
	player.y = 320;
	player.x_size = 48;
	player.y_size = 48;
	player.life = 3;
	player.safetime = 10;
	player.shot_trigger = 10;
	player.tomato = 50;
	player.speed = 5;
}

//�v���C���[�X�V�֐�
//�v���C���[�̓���Œǉ�������ꍇ�����ɏ����Ă���
void PlayerUpdate() {
	

	PlayerMovement();
	PlayerCollision();
	//�g���K�[��-1����
	player.shot_trigger--;
	//Z�L�[��������Ă��āA���g���K�[��0�ȉ���������e�ۂ𔭎˂���
	if (key_z > 0 && player.shot_trigger <= 0) {
		PlayerShot();
		player.tomato -= 1;
	}
	if (key_up == 1) {
		PlayerSpeedUp();
	}
	else if(key_down == 1 && player.speed >= 1){
		PlayerSpeedDown();
	}
	//DrawFormatString(300, 300, GetColor(255, 255, 255), "life �̒l�� %d �ł�", player.life);
}

//�v���C���[��`��
void PlayerDraw() {
	/*	player_safetime��2�Ŋ������]����Z�o���A���ꂪ0�Ȃ�Ε`�悷��悤�ɂ���
	����ƁA�Z�[�t�^�C�����̓v���C���[���_�ł���悤�ɂȂ�
	*/
	if (player.safetime % 2 == 0)
		DrawGraph(player.x, player.y, player.graphic[0], TRUE);
	
	DrawGraph(220, 450, speed_meter_graphic, TRUE);
	DrawRotaGraph2(220, 450, 20, 40, 1.0, (PI * (double)(player.speed / 10.0) - PI/2), speed_needle_graphic, TRUE);
}

///
void PlayerMovement() {
	//�L�[��������Ă�����v���C���[���ړ�������
	//if (key_up > 0)		player.y -= 4;
	//if (key_down > 0)	player.y += 4;
	if (key_left > 0)	player.x -= 4;
	if (key_right > 0)	player.x += 4;
	//�v���C���[����ʊO�ɏo�Ȃ��悤�ɂ���
	if (player.x < 0)			player.x = 0;
	if (player.x + 40 > 440)	player.x = 440 - 40;
	if (player.y < 0)			player.y = 0;
	if (player.y + 40 > 480)	player.y = 480 - 40;
}

void PlayerShot() {

	//�g�p����Ă��Ȃ��e�ۂ�T���A������������Z�b�g���Ĕ����o��
	for (int i = 0; i < player.tomato; i++) {
		if (shot[i].life == 0) {
			shot[i].life = 1;
			shot[i].x_size = 20;
			shot[i].y_size = 20;
			shot[i].x = player.x + player.x_size / 2 - shot[i].x_size / 2;
			shot[i].y = player.y;

			//�g���K�[��ݒ�
			player.shot_trigger = 10;
			break;		//���[�v����E�o
		}
	}
}

void PlayerCollision() {
	//for (int i = 0; i < MAX_TOMATO; i++) {
	//if (item[i].x <= player.x + player.x_size && item[i].x + item[i].x_size >= player.x) {
	//	if (item[i].y <= player.y + player.y_size && item[i].y + item[i].y_size[i] >= player.y) {
	//		player.tomato += 5;
	//		}
	//	}	
	//}
	if (player.safetime > 0)
		player.safetime--;
	else {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (enemy[i].x <= player.x + player.x_size && enemy[i].x + enemy[i].x_size >= player.x) {
				if (enemy[i].y <= player.y + player.y_size && enemy[i].y + enemy[i].y_size >= player.y) {
					player.life -= 1;
					player.safetime = 60;
					if (player.life == 0) {
						mode = GAMEOVER;
					}
				}
			}
		}
	}
}

void PlayerSpeedUp() {
	player.speed += 1;
}

void PlayerSpeedDown() {
	player.speed -= 1;
}