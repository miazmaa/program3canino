#include "kirby.h"
#include <allegro5\allegro.h> 
#include <iostream>
kirby::kirby(int HEIGHT, int WIDTH) {
	image = al_load_bitmap("warpstar.png");
	int popstar_height = HEIGHT / 8;
	x = (WIDTH / 2) - (al_get_bitmap_width(image) / 2);
	y = HEIGHT - (HEIGHT / 8) - al_get_bitmap_height(image);
	lives = 5;
	speed = 7;
	boundx = al_get_bitmap_width(image);
	boundy = al_get_bitmap_height(image);
	score = 0;
	angle = 128.0f;
}
kirby::~kirby() {
	al_destroy_bitmap(image);
}
void kirby::DrawKirby() {
	al_draw_rotated_bitmap(
		image, boundx / 2, boundy / 2, x + boundx / 2, y + boundy / 2, -(angle - 90) * ALLEGRO_PI / 180.0f, 0);
}
void kirby::RotateLeft()
{
	angle += 2.0f;

	if (angle > 150.0f)
		angle = 150.0f;
}
void kirby::RotateRight()
{
	angle -= 2.0f;

	if (angle < 30.0f)
		angle = 30.0f;
}
