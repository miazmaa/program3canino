#include "kirby.h"
#include <allegro5\allegro.h> 
#include <iostream>
kirby::kirby(int HEIGHT, int WIDTH) {
	image = al_load_bitmap("warpstar.png");
	int popstar_height = HEIGHT / 8;
	x = 20;
	y = HEIGHT - (HEIGHT / 8) - al_get_bitmap_height(image);
	lives = 5;
	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	score = 0;
}
kirby::~kirby() {
	al_destroy_bitmap(image);
}
void kirby::DrawKirby() {
	al_draw_bitmap(image, x, y, 0);
}
void kirby::MoveLeft() {
	x -= speed;
	if (x < 0)
		x = 0;
}
void kirby::MoveRight(int SCREEN_W) {
	x += speed;
	if (x > SCREEN_W - boundx) {
		x = SCREEN_W - boundx;
	}
}
