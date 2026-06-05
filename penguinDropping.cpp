#include "penguinDropping.h" 
#include <allegro5\allegro.h> 
#include <cstdlib> 

penguinDropping::penguinDropping() {
	waddle_doo = al_load_bitmap("waddledoo.png");
	live = false;
	speed = 2;
	boundx = 32;
	boundy = 32;
}
penguinDropping::~penguinDropping() {
	al_destroy_bitmap(waddle_doo);
}
void penguinDropping::DrawPenguin() {
	if (live)
	{
		al_draw_scaled_bitmap(waddle_doo, 0, 0, al_get_bitmap_width(waddle_doo), al_get_bitmap_height(waddle_doo), x, y, 32, 32, 0);
	}
}
void penguinDropping::StartPenguin(int WIDTH, int HEIGHT) {
	if (!live)
	{
		if (rand() % 500 == 0)
		{
			live = true;
			x = rand() % (WIDTH - boundx);
			y = -boundy;

		}
	}
}
void penguinDropping::UpdatePenguin() {
	if (live)
	{
		y += speed;
		int popstar_top_y = 420;
		if (y + boundy >= popstar_top_y) {
			live = false;
		}
	}
}

