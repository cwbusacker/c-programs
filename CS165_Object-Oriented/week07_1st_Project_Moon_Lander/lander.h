/***********************************************************************
* Header File:
*    Lander : Draw the Lander on the screen
* Author:
*    Chase Busacker
* Summary:
*    Definition for the lander class
************************************************************************/


#ifndef LANDER_H
#define LANDER_H

#include <iostream>
#include "point.h"
#include "velocity.h"
#include "uiDraw.h"

/*********************************************
* LANDER
* Position of the lander and the task of drawing
* it on the screen.
*********************************************/
class Lander
{
public:
  Lander();
  void setFuel(int fuel);
  Point getPoint() const;
  Velocity getVelocity() const;
  void setCanThrust();
  bool isAlive();
  bool isLanded();
  void applyGravity(float gravity);
  void setAlive(bool checkAlive);
  void setLanded(bool checkLanded);
  void applyThrustBottom();
  void applyThrustLeft();
  void applyThrustRight();
  void draw();
  bool getCanThrust();
  int getFuel();
  void drawNumber(Point fuelLocation, int fuelNumber);
private:
   int fuel;
   Point landerPoint;
   Velocity landerVelocity;
   void setLanderPoint();
   bool canThrust;
   bool landed;
   bool alive;
};

#endif
