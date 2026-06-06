#pragma once
#include "waddledooDropping.h" 
#include <allegro5\allegro.h>
#include "kirby.h"
class stars

{
public:
   stars();
   ~stars();
   void DrawStars();
   void FireStars(kirby& player);
   void UpdateStar();
   void CollideStar(waddledooDropping WaddleDoos[], int cSize);
   bool getLive() { return live; }
   void setLive(bool l) { live = l; }
private:
   int x;
   int y;
   bool live;
   int speed;
   float radian_angle;
   ALLEGRO_BITMAP *star;
};
