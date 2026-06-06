#include "waddledooDropping.h" 
#include <allegro5\allegro.h> 
#include <cstdlib> 

waddledooDropping::waddledooDropping() {
	waddle_doo = al_load_bitmap("waddledoo.png");
	live = false;
	speed = 2;
	boundx = 32;
	boundy = 32;
}
waddledooDropping::~waddledooDropping() {
	al_destroy_bitmap(waddle_doo);
}
void waddledooDropping::DrawWaddledoo() {
	if (live)
	{
		al_draw_scaled_bitmap(waddle_doo, 0, 0, al_get_bitmap_width(waddle_doo), al_get_bitmap_height(waddle_doo), x, y, 32, 32, 0);
	}
}
void waddledooDropping::StartWaddledoo(int WIDTH, int HEIGHT) {
	if (!live)
	{
		if (rand() % 200 == 0)
		{
			live = true;
			x = rand() % (WIDTH - boundx);
			y = -boundy;

		}
	}
}
void waddledooDropping::UpdateWaddledoo() {
	if (live)
	{
		y += speed;
	}
}
bool waddledooDropping::CollideWaddledoo(ALLEGRO_BITMAP& popstar) {
	if (live) {
		int popstar_bound = 480 - (480 / 8); //covers 1/8 of the screen, 480 / 8 = 60, so deletes waddle doo when it touches here
		if (y + boundy >= popstar_bound) {
			live = false; 
			return true;
		}
	}
	return false;
}

