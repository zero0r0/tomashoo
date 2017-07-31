#include "DxLib.h"
#include "data.h"
#include "Key.h"

//30���G�b�O�ύX
#define MAX_SPEED 10.0
//30���G�b�O�ύX
int length = 0;

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
	player.r = 10;
	//25���G�b�O�ύX
	player.time = TIME_LIMIT;
	player.fleam_count = 0;
}

//�v���C���[�X�V�֐�
//�v���C���[�̓���Œǉ�������ꍇ�����ɏ����Ă���
void PlayerUpdate() {
	
	//�A�j���[�V����
	if (player.count > 10) {
		player.anim_count++;
		player.count = 0;
	}
	else {
		player.count++;
	}

	//25���G�b�O�ύX
	if (player.fleam_count % 60 == 0 && !is_clear
		) {
		player.time--;
	}
	player.fleam_count++;

	PlayerMovement();
	PlayerCollision();
	//�g���K�[��-1����
	player.shot_trigger--;
	//Z�L�[��������Ă��āA���g���K�[��0�ȉ���������e�ۂ𔭎˂���
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
	//DrawFormatString(300, 300, , "life �̒l�� %d �ł�", player.life);
}

//�v���C���[��`��
void PlayerDraw() {
	/*	player_safetime��2�Ŋ������]����Z�o���A���ꂪ0�Ȃ�Ε`�悷��悤�ɂ���
	����ƁA�Z�[�t�^�C�����̓v���C���[���_�ł���悤�ɂȂ�
	*/
	//if (player.safetime % 2 == 0)
	//	DrawGraph(player.x, player.y, player.graphic[player.anim_count%2], TRUE);
	if (player.safetime % 2 == 0) {
		//30���G�b�O�ύX
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
	//30���G�b�O�ύX
	DrawGraph(230, 400, font_num_graphic[0], true);
	DrawGraph(195, 400, font_num_graphic[5], true);
	DrawGraph(160, 400, font_num_graphic[0], true);
	DrawGraph(30, 365, font_tomato_graphic, true);

	//�v���C���[�̋����̕`��
	//25���G�b�O�ύX
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
	//�L�[��������Ă�����v���C���[���ړ�������
	//if (key_up > 0)		player.y -= 4;
	//if (key_down > 0)	player.y += 4;
	if (key_left > 0)	player.x -= 4;
	if (key_right > 0)	player.x += 4;
	//�v���C���[����ʊO�ɏo�Ȃ��悤�ɂ���
	if (player.x < 0)			player.x = 0;
	if (player.x  > 640)	player.x = 640;
	if (player.y < 0)			player.y = 0;
	if (player.y  > 480)	player.y = 480;
}

void PlayerShot() {

	//�g�p����Ă��Ȃ��e�ۂ�T���A������������Z�b�g���Ĕ����o��
	for (int i = 0; i < player.tomato; i++) {
		if (!shot[i].is_active) {
			shot[i].is_active = true;
			shot[i].x_size = 48;
			shot[i].y_size = 48;
			shot[i].x = player.x + player.x_size / 2 - shot[i].x_size / 2;
			//27���G�b�O�ύX
			shot[i].y = player.y - 30;
			//�g���K�[��ݒ�
			player.shot_trigger = 10;
			break;		//���[�v����E�o
		}
	}
}

void PlayerCollision() {
	for (int i = 0; i < MAX_TOMATO; i++) {
		if ((player.x + player.x_size / 2 - (item[i].x + item[i].x_size / 2))* (player.x + player.x_size / 2 - (item[i].x + item[i].x_size / 2)) + (player.y + player.y_size / 2 - (item[i].y + item[i].y_size / 2))* (player.y + player.y_size / 2 - (item[i].y + item[i].y_size / 2)) <= (player.r + item[i].r)*(player.r + item[i].r)) {
			player.tomato += 5;
			item[i].y = -100;
			item[i].x = -100;
		}
	}
	
	if (player.safetime > 0)
		player.safetime--;
	else {
		for (int i = 0; i < MAX_ENEMY; i++) {
			if ((player.x + player.x_size / 2 - (enemy[i].x + enemy[i].x_size / 2))*(player.x + player.x_size / 2 - (enemy[i].x + enemy[i].x_size / 2)) + (player.y + player.y_size / 2 - (enemy[i].y + enemy[i].y_size / 2))*(player.y + player.y_size / 2 - (enemy[i].y + enemy[i].y_size / 2)) <= (player.r + enemy[i].r)*(player.r + enemy[i].r)) { //22���G�b�O�ύX
				//player.life -= 1;
				Damage(enemy[i].type);
				player.safetime = 60;
				if (enemy[i].type == 2 || 4 <= enemy[i].type) {
					GameoverInit(3);
				}
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
			player.speed--;
			break;
		default:
			scene = GAMEOVER;
			return;
			break;
	}
	player.tomato -= damage;
}

void PlayerSpeedUp() {
	player.speed += 1;
}

void PlayerSpeedDown() {
	player.speed -= 1;
}