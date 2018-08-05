#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 5
#define BULLET_LIFE 40

#include "flyingObject.h"
#include "point.h"

class Bullets:public flyingObjects
{

public:
   void fire(Point point, float angle, Velocity shipVelocity);
   virtual void advance();
   virtual void draw();
private:
   int drawcount;
      
};


#endif /* bullet_h */
