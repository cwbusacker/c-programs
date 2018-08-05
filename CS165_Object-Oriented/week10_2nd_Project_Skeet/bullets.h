#ifndef BULLETS_H
#define BULLETS_H

#include "flyingObjects.h"



class Bullet: public flyingObjects
{
public:
   Bullet();
   virtual void draw();
   void fire(Point point, float angle);
   virtual void advance();
};

#endif //BULLETS_H