#include "DxLib.h"
#include "data.h"
#include "Key.h"


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
	player.speed = 1;
	player.count = 0;
	player.anim_count = 0;
	player.r = 7;
}

//�v���C���[�X�V�֐�
//�v���C���[�̓���Œǉ�������ꍇ�����ɏ����Ă���
void PlayerUpdate() {
	
	if (player.count > 10) {
		player.anim_count++;
		player.count = 0;
	}
	else {
		player.count++;
	}
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
	//DrawFormatString(300, 300, , "life �̒l�� %d �ł�", player.life);
}

//�v���C���[��`��
void PlayerDraw() {
	/*	player_safetime��2�Ŋ������]����Z�o���A���ꂪ0�Ȃ�Ε`�悷��悤�ɂ���
	����ƁA�Z�[�t�^�C�����̓v���C���[���_�ł���悤�ɂȂ�
	*/
	if (player.safetime % 2 == 0)
		DrawGraph(player.x, player.y, player.graphic[player.anim_count%2], TRUE);
	
	DrawGraph(150, 440, speed_meter_graphic, TRUE);
	DrawRotaGraph2(335, 490, 20, 40, 1.0, (PI * (double)(player.speed / 10.0) - PI/2), speed_needle_graphic, TRUE);
	DrawGraph(100, 400, font_num_graphic[player.tomato%10], true);
	DrawGraph(65, 400, font_num_graphic[(player.tomato /10 ) %10], true);
	DrawGraph(30, 400, font_num_graphic[(player.tomato /100 ) %10], true);
	DrawGraph(140, 400, shasen_graphic, true);
	DrawGraph(30, 365, font_tomato_graphic, true);
	//DrawCircle(player.x + 24, player.y + 24, player.r, GetColor(255, 255, 255), true);
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
	if (player.x + 40 > 480)	player.x = 480 - 40;
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
	for (int i = 0; i < MAX_TOMATO; i++) {
	if (item[i].x <= player.x + player.x_size / 2  && item[i].x + item[i].x_size >= player.x + player.x_size / 2) {
		if (item[i].y <= player.y + player.y_size / 2 && item[i].y + item[i].y_size >= player.y + player.y_size / 2) {
				player.tomato += 5;
				item[i].y = -100;
				item[i].x = -100;
			}
		}	
	}
	if (player.safetime > 0)
		player.safetime--;
	else {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if (enemy[i].x <= player.x + player.x_size / 2 && enemy[i].x + enemy[i].x_size >= player.x + player.x_size / 2) {
				if (enemy[i].y <= player.y + player.y_size / 2 && enemy[i].y + enemy[i].y_size >= player.y + player.y_size / 2) {
					player.life -= 1;
					player.safetime = 60;
					if (enemy[i].type == 2 || enemy[i].type == 3 || enemy[i].type == 5) {
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