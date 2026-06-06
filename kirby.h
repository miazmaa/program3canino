#ifndef PLAYERH
#define PLAYERH
#include <allegro5\allegro.h>
class kirby
{
public:
	kirby(int HEIGHT, int WIDTH);
	~kirby();
	void DrawKirby();
	void RotateLeft();
	void RotateRight();
	int getBoundX() { return boundx; }
	int getBoundY() { return boundy; }
	int getX() { return x; }
	int getY() { return y; }
	float getAngle() { return angle; }
	int getLives() { return lives; }
	int getScore() { return score; }
	void addScore() { score++; }
private:
	void update_image();
	int x;
	int y;
	float angle;
	int lives;
	int speed;
	int boundx;
	int boundy;
	int score;
	ALLEGRO_BITMAP* image;
};
#endif