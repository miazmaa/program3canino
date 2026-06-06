#include <allegro5\allegro.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "waddledooDropping.h"
#include "kirby.h"
#include "star.h"
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
	bool redraw = true;
	ALLEGRO_BITMAP* space = NULL;
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
	popstar = al_load_bitmap("popstar.png");
	ALLEGRO_FONT* rubik = al_load_ttf_font("rubik.ttf", 20, 0);
	const int NUM_WADDLE_DOOS = 15;
	const int NUM_STARS = 10;;
	enum KEYS { LEFT, RIGHT, SPACE };
	bool keys[3] = { false, false, false };
	waddledooDropping waddleDoos[NUM_WADDLE_DOOS];
	stars starsArray[NUM_STARS];
	kirby player(SCREEN_H, SCREEN_W);
	event_queue = al_create_event_queue();
	if (!event_queue) {
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}
	al_install_keyboard();

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_flip_display();

	al_start_timer(timer);

	while (1)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_LEFT: keys[0] = true; break;
			case ALLEGRO_KEY_RIGHT: keys[1] = true; break;
			case ALLEGRO_KEY_SPACE: keys[2] = true; break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_LEFT: keys[0] = false; break;
			case ALLEGRO_KEY_RIGHT: keys[1] = false; break;
			case ALLEGRO_KEY_SPACE: keys[2] = false; break;
			}
		}
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (!game_over) {
				if (keys[0]) {
					player.RotateLeft();
				}
				if (keys[1]) {
					player.RotateRight();
				}
				if (keys[2]) {
					for (int i = 0; i < NUM_STARS; i++) {
						if (!starsArray[i].getLive()) {
							starsArray[i].FireStars(player);
							break;
						}
					}
				}
				for (int i = 0; i < NUM_STARS; i++)
				{
					starsArray[i].UpdateStar();
					starsArray[i].CollideStar(waddleDoos, NUM_WADDLE_DOOS);
				}
				for (int i = 0; i < NUM_WADDLE_DOOS; i++) {

					waddleDoos[i].StartWaddledoo(SCREEN_W, SCREEN_H);
					waddleDoos[i].UpdateWaddledoo();

					if (waddleDoos[i].CollideWaddledoo(*popstar)) {
						hits++;
						if (hits >= 5)
							game_over = true;
					}
				}
				redraw = true;
			}
			if (redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;
				al_clear_to_color(al_map_rgb(0, 0, 0));
				if (!game_over) {
					al_draw_bitmap(space, 0, 0, 0);
					int popstar_height = SCREEN_H / 8;
					al_draw_scaled_bitmap(popstar, 0, 0, al_get_bitmap_width(popstar), al_get_bitmap_height(popstar), 0, SCREEN_H - popstar_height, SCREEN_W, popstar_height, 0);
					player.DrawKirby();
					for (int i = 0; i < NUM_STARS; i++)
					{
						starsArray[i].DrawStars();
					}
					for (int i = 0; i < NUM_WADDLE_DOOS; i++) {
						waddleDoos[i].DrawWaddledoo();
					}
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
	}
	al_destroy_bitmap(space);
	al_destroy_bitmap(popstar);
	al_destroy_timer(timer);
	al_destroy_font(rubik);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	system("pause");
	return 0;
}