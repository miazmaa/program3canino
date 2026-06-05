#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "waddledooDropping.h"
#include "snowballs.h"
#include <iostream>
#include <ctime>

int main(int argc, char** argv) {

	const float FPS = 60;
	const int SCREEN_W = 640;
	const int SCREEN_H = 480;
	const int kirby_SIZE = 32;
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	ALLEGRO_TIMER* timer = NULL;

	float duck_x = SCREEN_W / 2.0 - kirby_SIZE / 2.0;
	float duck_y = SCREEN_H / 2.0 - kirby_SIZE / 2.0;
	float duck_dx = -4.0, duck_dy = 4.0;
	bool redraw = true;
	ALLEGRO_BITMAP* space = NULL;
	ALLEGRO_BITMAP* kirby = NULL;
	ALLEGRO_BITMAP* popstar = NULL;
	srand(time(NULL)); //for seeding enemy placement later
	if (!al_init()) {
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display) {
		al_destroy_timer(timer);
		return -1;
	}



	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	int hits = 0;
	bool game_over = false;
	int planet_top = SCREEN_H - (SCREEN_H / 8);
	space = al_load_bitmap("space.png");
	kirby = al_load_bitmap("warpstar.png");
	popstar = al_load_bitmap("popstar.png");
	ALLEGRO_FONT* rubik = al_load_ttf_font("rubik.ttf", 20, 0);
	al_convert_mask_to_alpha(kirby, al_map_rgb(255, 0, 255));
	const int NUM_WADDLE_DOOS = 10;
	waddledooDropping waddleDoos[NUM_WADDLE_DOOS];
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_destroy_bitmap(kirby);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (!game_over) {
				if (duck_x < 0 || duck_x > SCREEN_W - kirby_SIZE) {
					duck_dx = -duck_dx;
				}
				if (duck_y < 0 || duck_y > SCREEN_H - kirby_SIZE) {
					duck_dy = -duck_dy;
				}
				duck_x += duck_dx;
				duck_y += duck_dy;
				for (int i = 0; i < NUM_WADDLE_DOOS; i++) {
					waddleDoos[i].StartWaddledoo(SCREEN_W, SCREEN_H);
					waddleDoos[i].UpdateWaddledoo();
					if (waddleDoos[i].CollideWaddledoo(*popstar)) {
						hits++;
						if (hits >= 5) {
							game_over = true;
						}
					}
				}
			}
			redraw = true;
		}
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));
			if (!game_over) {
				al_draw_bitmap(space, 0, 0, 0);
				int star_position = SCREEN_H / 8;
				al_draw_scaled_bitmap(popstar, 0, 0, al_get_bitmap_width(popstar), al_get_bitmap_height(popstar), 0, SCREEN_H - star_position, SCREEN_W, star_position, 0);
				for (int i = 0; i < NUM_WADDLE_DOOS; i++) {
					waddleDoos[i].DrawWaddledoo();
				}
				al_draw_bitmap(kirby, duck_x, duck_y, 0);
				al_flip_display();
			}
			else {
				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(rubik, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 20, ALLEGRO_ALIGN_CENTER, "Game Over!");
				al_flip_display();
				al_rest(5.0);
				break;
			}
		}
	}

	al_destroy_bitmap(kirby);
	al_destroy_bitmap(space);
	al_destroy_bitmap(popstar);
	al_destroy_timer(timer);
	al_destroy_font(rubik);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	system("pause");
	return 0;
}