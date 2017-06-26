#pragma once

/*　キーの入力状況を入れる。
押している間は値が1ずつ増えていく。離すと0になる。
*/
extern int key_z, key_up, key_down, key_left , key_right;

void KeyUpdate();
