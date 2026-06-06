#include "waddledooDropping.h" 
#include "star.h"
#include <allegro5\allegro.h> 
#include <cstdlib> 
stars::stars() {
	speed = 10;
	live = false;
	star = al_load_bitmap("star.png");
}
stars::~stars() {
	al_destroy_bitmap(star);
}
void stars::DrawStars() {
	if (live) {
		al_draw_scaled_bitmap(star, 0, 0, al_get_bitmap_width(star), al_get_bitmap_height(star), x, y, 32, 32, 0);
	}
}
void stars::FireStars(kirby& player) {
	if (!live)
	{
		live = true;

		x = player.getX() + player.getBoundX() / 2 - 16;
		y = player.getY();
	}
}
void stars::UpdateStar() {
	if (live) {
		const int BALL_SPEED = speed;
		x += BALL_SPEED * cos(radian_angle);
		y -= BALL_SPEED * sin(radian_angle);
		if (y < -32 || y > 480 || x < -32 || x > 640) { //check to see if star left screen, is 32x32
			live = false;
		}
	}

}
void stars::CollideStar(waddledooDropping WaddleDoos[], int cSize) {
	if (live)
	{
		for (int j = 0; j < cSize; j++)
		{
			if (WaddleDoos[j].getLive())
			{
				if (x > (WaddleDoos[j].getX() - WaddleDoos[j].getBoundX()) &&
					x < (WaddleDoos[j].getX() + WaddleDoos[j].getBoundX()) &&
					y >(WaddleDoos[j].getY() - WaddleDoos[j].getBoundY()) &&
					y < (WaddleDoos[j].getY() + WaddleDoos[j].getBoundY()))
				{
					live = false;
					WaddleDoos[j].setLive(false);
				}
			}
		}
	}
}