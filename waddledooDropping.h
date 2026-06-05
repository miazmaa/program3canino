#pragma once
#include <allegro5\allegro.h>
class waddledooDropping
{
public:
    waddledooDropping();
    ~waddledooDropping();
    void DrawWaddledoo();
    void StartWaddledoo(int WIDTH, int HEIGHT);
    void UpdateWaddledoo();
    bool CollideWaddledoo(ALLEGRO_BITMAP& popstar);
    int getBoundX() { return boundx; }
    int getBoundY() { return boundy; }
    int getX() { return x; } 
    int getY() { return y; }
    bool getLive() { return live; }
    void setLive(bool l) { live = l; }
private:
    int x;
    int y;
    bool live;
    int speed;
    int boundx;
    int boundy;
    ALLEGRO_BITMAP* waddle_doo;
};