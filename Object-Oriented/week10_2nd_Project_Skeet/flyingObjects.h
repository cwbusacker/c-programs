#ifndef FLYING_OBJECTS_H
#define FLYING_OBJECTS_H

#include "point.h"
#include "velocity.h"

class flyingObjects
{
protected:
   Point location;
   Velocity velocity;
   bool alive;
public:
   Point getPoint();
   void setPoint(float x, float y);
   Velocity getVelocity();
   void setVelocity(float dx, float dy);
   bool isAlive();
   virtual void advance() = 0;
   virtual void kill();
};

#endif
