#ifndef FLYING_OBJECTS_H
#define FLYING_OBJECTS_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

class flyingObjects
{
protected:
   Point location;
   Velocity velocity;
   bool alive;
public:
   flyingObjects();
   Point getPoint() const;
   void setPoint(float x, float y);
   Velocity getVelocity() const;
   void setVelocity(float dx, float dy);
   bool isAlive() const;
   virtual void advance() = 0;
   void kill();
   virtual void draw() = 0;
};

#endif